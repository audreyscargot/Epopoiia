// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

#include <string>

#include "K2Node_GetDataTableRow.h"
#include "Epopoiia/Core/GameInstanceMain.h"
#include "Epopoiia/Core/ItemStruct.h"
#include "Epopoiia/Interface/PickUpInterface.h"
#include "Epopoiia/Objects/FixableObject.h"
#include "Epopoiia/Objects/InteractableObject.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Runtime/Datasmith/DatasmithCore/Public/DatasmithDefinitions.h"


// Sets default values
AWorldManager::AWorldManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();
	ManageWorld();
	
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorldManager::ManageWorld()
{
	//Place all registered objects
	GameInstance = Cast<UGameInstanceMain>(UGameplayStatics::GetGameInstance(this));
	WorldState = GameInstance->GetTempleState();
	UE_LOG(LogTemp, Warning, TEXT("ManageWorld"))
	for (auto i : WorldState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Object placed"))
		FName s = UKismetStringLibrary::Conv_StringToName(UKismetStringLibrary::Conv_IntToString(i.index));
		FItemStruct* _itemStruct = nullptr;
		if (DataTable) _itemStruct = DataTable->FindRow<FItemStruct>(s, "", true);
		FActorSpawnParameters spawnParams;
		
		if (_itemStruct)
		{
			TSubclassOf<AInteractableObject> _classToSpawn = _itemStruct->actorClass;
			AInteractableObject* _tempObj = GetWorld()->SpawnActorDeferred<AInteractableObject>(_classToSpawn, i.transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn, ESpawnActorScaleMethod::MultiplyWithRoot);
			_tempObj->ID = _itemStruct->ID;
			if (AFixableObject* _tempFixActor = Cast<AFixableObject>(_tempObj))
			{
				FixFurniture(_tempFixActor, i.isFixed);
			}
			_tempObj->FinishSpawning(i.transform);
		}
	}
	FixTempleState();
}

void AWorldManager::FixFurniture(AFixableObject* _obj, bool _isFixed)
{
	if (_obj)
	{
		_obj->isFixed = _isFixed;
	}
}

void AWorldManager::FixTempleState()
{
	TArray<AActor*> _actorInScene;
	TArray<AFixableObject*> _fixableObjects;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFixableObject::StaticClass(), _actorInScene);
	for (AActor* actor : _actorInScene)
	{
		if (!actor->FindComponentByClass<UPickUpInterface>())
		{
			AFixableObject* _fixActor = Cast<AFixableObject>(actor); 
			if (_fixActor)
			{
				_fixableObjects.Add(_fixActor);
			}
		}
	}
	TMap<int, bool> _tempFixed = GameInstance->GetTempleFixedState();
	for (auto _fixable : _tempFixed)
	{
		for (auto _fixActor : _fixableObjects)
		{
			if (_fixActor->ID == _fixable.Key)
			{
				_fixActor->isFixed = _fixable.Value;
				_fixActor->MakeMesh();
				_fixableObjects.RemoveSingle(_fixActor);
				break;
			}
		}
	}
}

