// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceMain.h"

#include "GroomVisualizationData.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameEpopoiia.h"
#include "Epopoiia/Interface/InventoryComponent.h"
#include "Epopoiia/Interface/PickUpInterface.h"
#include "Epopoiia/Objects/FixableObject.h"
#include "Epopoiia/Objects/InteractableObject.h"
#include "Kismet/GameplayStatics.h"

const FString saveName = "EpopoiiaSave";
const TSubclassOf<USaveGameEpopoiia> saveGameClass = USaveGameEpopoiia::StaticClass();

void UGameInstanceMain::Init()
{
	Super::Init();
	bool isSaveGameValid;
	isSaveGameValid = UGameplayStatics::DoesSaveGameExist(saveName, 0);
	if (!isSaveGameValid)
	{
		currentSaveGame = Cast<USaveGameEpopoiia>(UGameplayStatics::CreateSaveGameObject(saveGameClass));
		UGameplayStatics::SaveGameToSlot(currentSaveGame, saveName, 0);
		UE_LOG(LogTemp, Warning, TEXT("Save Created"));
	}
	else
	{
		currentSaveGame = Cast<USaveGameEpopoiia>(UGameplayStatics::LoadGameFromSlot(saveName, 0));
		UE_LOG(LogTemp, Warning, TEXT("Save Loaded"));
		setSavedVariables();
	}
}


TArray<FFurnitureState> UGameInstanceMain::GetTempleState()
{
	for (auto i : TempleState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Temple State: %i"), i.index)
	}
	return TempleState;
}

TMap<int, bool> UGameInstanceMain::GetTempleFixedState()
{
	return TempleFixedState;
}

int UGameInstanceMain::GetSeed()
{
	return seed;
}

void UGameInstanceMain::SetSeed(int _newSeed)
{
	seed = _newSeed;
}

TArray<FNPCsQuest> UGameInstanceMain::GetQuestsOfDay()
{
	return questsOfDay;
}

void UGameInstanceMain::AddQuestsOfDay(FNPCsQuest _quest)
{
	questsOfDay.Add(_quest);
	UE_LOG(LogTemp, Warning, TEXT("QuestsOfDay Added"));
	UE_LOG(LogTemp, Warning, TEXT("quests quantity %i"), questsOfDay.Num());
}

void UGameInstanceMain::UpdateQuestsOfDay(FNPCsQuest _quest)
{
	questsOfDay[_quest.npcID] = _quest;
}


//--------SAVE FUNCTIONS-----------

void UGameInstanceMain::SaveInventory()
{
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	TSubclassOf<UInventoryComponent> inventoryClass = UInventoryComponent::StaticClass();
	playerInventory = Cast<UInventoryComponent>(player->GetComponentByClass(inventoryClass))->GetInventory();
	currentSaveGame->SetPlayerInventory(playerInventory);
}

void UGameInstanceMain::SaveSeed()
{
	currentSaveGame->SetSeed(seed);
}

void UGameInstanceMain::SaveShopState()
{
	currentSaveGame->SetShopState(shopState);
}

void UGameInstanceMain::SaveTemple()
{
	//Registering all interactables actors in the scene
	TArray<AActor*> _actorInScene;
	TArray<AInteractableObject*> _objectsInScene;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractableObject::StaticClass(), _actorInScene);
	for (AActor* Actor : _actorInScene)
	{
		if (Actor->FindComponentByClass(UPickUpInterface::StaticClass()))
		{
			AInteractableObject* _objectTemp = Cast<AInteractableObject>(Actor);
			if (_objectTemp)
			{
				_objectsInScene.Add(_objectTemp);
			}
		}
	}
	
	//Make Array of furniture struct
	TArray<FFurnitureState> _currentFurnitureStates;
	for (AInteractableObject* Actor : _objectsInScene)
	{
		AFixableObject* _tempActor = Cast<AFixableObject>(Actor);
		bool _isFixed = _tempActor != nullptr ? _tempActor->isFixed: false;
		UE_LOG(LogTemp, Warning, TEXT("IsFixed %d"), _isFixed);
		FFurnitureState _objectState = FFurnitureState(Actor->ID, Actor->GetActorLocation(),Actor->GetTransform(), _isFixed);
		_currentFurnitureStates.Add(_objectState);
		UE_LOG(LogTemp, Warning, TEXT("Saved"));
	}
	
	TempleState = _currentFurnitureStates;
	SaveFixedTemple(_objectsInScene);
	currentSaveGame->SetTempleState(TempleState);
	
}

void UGameInstanceMain::SaveFixedTemple(TArray<AInteractableObject*> _registeredActors)
{
	TArray<AActor*> _actorInScene;
	TArray<AInteractableObject*> _objectsInScene;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFixableObject::StaticClass(), _actorInScene);
	for (AActor* Actor : _actorInScene)
	{
		AFixableObject* _objectTemp = Cast<AFixableObject>(Actor);
		if (_objectTemp)
		{
			int _index;
			if (!_registeredActors.Find(_objectTemp, _index ))
			{
				TempleFixedState.Add(_objectTemp->ID, _objectTemp->isFixed);
			}
		}
	}
	currentSaveGame->SetFixedState(TempleFixedState);
}

void UGameInstanceMain::SaveQuests()
{
	currentSaveGame->SetQuests(questsOfDay);
}

void UGameInstanceMain::SaveGeneral()
{
	if (currentSaveGame)
	{
		currentSaveGame->SetTempleState(TempleState);
		currentSaveGame->SetFixedState(TempleFixedState);
		SaveInventory();
		SaveSeed();
		SaveShopState();
		SaveQuests();
		UGameplayStatics::SaveGameToSlot(currentSaveGame, saveName, 0);
		UE_LOG(LogTemp, Warning, TEXT("Saved General"));
	}
	
	//TODO : Add quests save (NPC state ?)
}

void UGameInstanceMain::ResetGameInstance()
{
	questsOfDay.Empty();
	shopState.Empty();
}

void UGameInstanceMain::setSavedVariables()
{
	if (currentSaveGame)
	{
		UE_LOG(LogTemp, Warning, TEXT("setVariables"));
		playerInventory = currentSaveGame->GetPlayerInventory();
		TempleState = currentSaveGame->GetTempleState();
		TempleFixedState = currentSaveGame->GetFixedState();
		shopState = currentSaveGame->GetShopState();
		questsOfDay = currentSaveGame->GetQuests();
	}
}


