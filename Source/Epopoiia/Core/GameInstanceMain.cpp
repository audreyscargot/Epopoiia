// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceMain.h"

#include "GroomVisualizationData.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameEpopoiia.h"
#include "Epopoiia/Objects/FixableObject.h"
#include "Epopoiia/Objects/InteractableObject.h"
#include "Kismet/GameplayStatics.h"

const FString saveName = FString("EpopoiiaSave");
const TSubclassOf<USaveGameEpopoiia> saveGameClass;

void UGameInstanceMain::Init()
{
	Super::Init();
	bool isSaveGameValid;
	isSaveGameValid = UGameplayStatics::DoesSaveGameExist(saveName, 0);
	if (!isSaveGameValid)
	{
		currentSaveGame = Cast<USaveGameEpopoiia>(UGameplayStatics::CreateSaveGameObject(saveGameClass));
		UGameplayStatics::SaveGameToSlot(currentSaveGame, saveName, 0);
	}
	else
	{
		currentSaveGame = Cast<USaveGameEpopoiia>(UGameplayStatics::LoadGameFromSlot(saveName, 0));
	} 
}

void UGameInstanceMain::SaveAll()
{
	
}

TArray<FFurnitureState> UGameInstanceMain::GetTempleState()
{
	return TempleState;
}

void UGameInstanceMain::SetTempleState(TArray<FFurnitureState> templeState)
{
	TempleState = templeState;
}

int UGameInstanceMain::GetSeed()
{
	return seed;
}

void UGameInstanceMain::SetSeed(int _newSeed)
{
	seed = _newSeed;
}

void UGameInstanceMain::SaveTemple()
{
	//Registering all interactables actors in the scene
	TArray<AActor*> _actorInScene;
	TArray<AInteractableObject*> _objectsInScene;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractableObject::StaticClass(), _actorInScene);
	for (AActor* Actor : _actorInScene)
	{
		AInteractableObject* _objectTemp = Cast<AInteractableObject>(Actor);
		if (!_objectTemp)
		{
			_objectsInScene.Add(_objectTemp);
		}
	}
	
	//Make Array of furniture struct
	TArray<FFurnitureState> _currentFurnitureStates;
	for (AInteractableObject* Actor : _objectsInScene)
	{
		AFixableObject* _tempActor = Cast<AFixableObject>(Actor);
		bool _isFixed = _tempActor != nullptr ? _tempActor->isFixed: false;
		FFurnitureState _objectState = FFurnitureState(Actor->ID, Actor->GetActorLocation(), _isFixed);
		_currentFurnitureStates.Add(_objectState);
	}
	
	TempleState = _currentFurnitureStates;
	UE_LOG(LogTemp, Warning, TEXT("Saved"));
}


