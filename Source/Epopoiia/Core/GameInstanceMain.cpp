// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceMain.h"

#include "GameFramework/SaveGame.h"
#include "SaveGameEpopoiia.h"
#include "Epopoiia/Interface/InventoryComponent.h"
#include "Epopoiia/Interface/PickUpInterface.h"
#include "Epopoiia/Interface/ReviewManagerComponent.h"
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
		InitVariables();
	}
	else
	{
		currentSaveGame = Cast<USaveGameEpopoiia>(UGameplayStatics::LoadGameFromSlot(saveName, 0));
		UE_LOG(LogTemp, Warning, TEXT("Save Loaded"));
		setSavedVariables();
	}
}

//---------------GETTER SETTER----------------------
TArray<FFurnitureState> UGameInstanceMain::GetTempleState()
{
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

int UGameInstanceMain::GetTimeRewindAbility()
{
	return playerTimeRewindAbilityLevel;
}

void UGameInstanceMain::SetTimeRewindAbility(int _toAdd)
{
	playerTimeRewindAbilityLevel += _toAdd;
	SavePlayerTimeRewindAbility();
	SaveGameToSlot();
	player->GettingStronger();
}

bool UGameInstanceMain::GetHasAltarBeenUsed()
{
	return hasAltarBeenUsed;
}

void UGameInstanceMain::SetHasAltarBeenUsed(bool _hasAltarBeenUsed)
{
	hasAltarBeenUsed = _hasAltarBeenUsed;
}

int UGameInstanceMain::GetReviewGrade()
{
	return templeReviewGrade;
}

void UGameInstanceMain::SetReviewGrade(int _reviewGrade)
{
	templeReviewGrade = _reviewGrade;
	SaveReviewGrade();
	SaveGameToSlot();
}

TArray<FReviewStruct> UGameInstanceMain::GetReviews()
{
	return reviews;
}

void UGameInstanceMain::SetReviews(TArray<FReviewStruct> _reviews)
{
	reviews = _reviews;
	SaveReviews();
	SaveGameToSlot();
}

int UGameInstanceMain::GetPlayerMoney()
{
	return playerMoney;
}

void UGameInstanceMain::SetPlayerMoney(int _playerMoney)
{
	playerMoney += _playerMoney;
}

TArray<int> UGameInstanceMain::GetPlayerInventory()
{
	return playerInventory;
}

TArray<FMythipediaPost> UGameInstanceMain::GetPlayerPosts()
{
	return playerPosts;
}

void UGameInstanceMain::SetPlayerPosts(TArray<FMythipediaPost> _playerPosts)
{
	playerPosts = _playerPosts;
}

TMap<FString, EVocabularyType> UGameInstanceMain::GetPlayerVocabulary()
{
	return playerVocabulary;
}

void UGameInstanceMain::SetPlayerVocabulary(TMap<FString, EVocabularyType> _vocabulary)
{
	playerVocabulary = _vocabulary;
}

TArray<FShopState> UGameInstanceMain::GetShopState()
{
	return shopState;
}

void UGameInstanceMain::SetShopState(TArray<FShopState> _shopState)
{
	shopState = _shopState;
}

TArray<FNPCsQuest> UGameInstanceMain::GetQuestsOfDay()
{
	return questsOfDay;
}

void UGameInstanceMain::AddQuestsOfDay(FNPCsQuest _quest)
{
	questsOfDay.Add(_quest);
	SaveQuests();
	SaveGameToSlot();
	
}

void UGameInstanceMain::UpdateQuestsOfDay(FNPCsQuest _quest)
{
	questsOfDay[_quest.npcID] = _quest;
}

void UGameInstanceMain::BuyObject(int _price, int _objectID, int _shopSlot)
{
	if (playerMoney >= _price)
	{
		if (player->Inventory->GetInventory().Num() < player->Inventory->inventorySlots)
		{
			playerMoney -= _price;
			player->Inventory->AddToInventory(_objectID);
			SuccessfullyBoughtDelegate.Broadcast(_shopSlot);
		}
	}
}

void UGameInstanceMain::UpdateGIInventory(UInventoryComponent* _inventory)
{
	playerInventory = _inventory->GetInventory();
}


//--------SAVE FUNCTIONS-----------

void UGameInstanceMain::SaveInventory()
{
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

void UGameInstanceMain::SaveFixedTemple(TArray<AInteractableObject*> _registeredActors) //registers all fixable elements of scene that are not pickables
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
		SaveAltar();
		SavePlayerMoney();
		SavePlayerTimeRewindAbility();
		SaveReviews();
		
		SaveGameToSlot();
	}
}

void UGameInstanceMain::SavePlayerTimeRewindAbility()
{
	currentSaveGame->SetPlayerTimeRewindAbility(playerTimeRewindAbilityLevel);
	SaveGameToSlot();
}

void UGameInstanceMain::SaveAltar()
{
	currentSaveGame->SetHasAltarBeenUsed(hasAltarBeenUsed);
	currentSaveGame->SetTempleReviewGrade(templeReviewGrade);
}

void UGameInstanceMain::SavePlayerMoney()
{
	currentSaveGame->SetPlayerMoney(playerMoney);
}

void UGameInstanceMain::SaveReviews()
{
	currentSaveGame->SetReviews(reviews);
}

void UGameInstanceMain::SaveReviewGrade()
{
	currentSaveGame->SetTempleReviewGrade(templeReviewGrade);
}

void UGameInstanceMain::SavePlayerVocabulary()
{
	currentSaveGame->SetPlayerVocabulary(playerVocabulary);
	SaveGameToSlot();
}

void UGameInstanceMain::SavePosts()
{
	currentSaveGame->SetPlayerPosts(playerPosts);
	SaveGameToSlot();
}

void UGameInstanceMain::SaveGameToSlot()
{
	UGameplayStatics::SaveGameToSlot(currentSaveGame, saveName, 0);
}

void UGameInstanceMain::ResetGameInstance()
{
	questsOfDay.Empty();
	currentSaveGame->SetQuests(questsOfDay);
	shopState.Empty();
	currentSaveGame->SetShopState(shopState);
	hasAltarBeenUsed = false;
	currentSaveGame->SetHasAltarBeenUsed(hasAltarBeenUsed);
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
		hasAltarBeenUsed = currentSaveGame->GetHasAltarBeenUsed();
		playerMoney = currentSaveGame->GetPlayerMoney();
		templeReviewGrade = currentSaveGame->GetTempleReviewGrade();
		seed = currentSaveGame->GetSeed();
		reviews = currentSaveGame->GetReviews();
		playerVocabulary = currentSaveGame->GetPlayerVocabulary();
		playerPosts = currentSaveGame->GetPlayerPosts();
		playerTimeRewindAbilityLevel = currentSaveGame->GetPlayerTimeRewindAbility();
	}
}

void UGameInstanceMain::InitVariables()
{
	currentSaveGame->SetPlayerMoney(playerMoney);
	currentSaveGame->SetTempleState(TempleState);
	
	SaveGameToSlot();
}


