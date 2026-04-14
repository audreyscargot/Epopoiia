// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

#include <string>

#include "K2Node_GetDataTableRow.h"
#include "Epopoiia/Core/GameInstanceMain.h"
#include "Epopoiia/Core/ItemStruct.h"
#include "Epopoiia/Objects/InteractableObject.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"


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
	GameInstance = Cast<UGameInstanceMain>(UGameplayStatics::GetGameInstance(this));
	WorldState = GameInstance->GetTempleState();
	for (auto i : WorldState)
	{
		FName s = UKismetStringLibrary::Conv_StringToName(UKismetStringLibrary::Conv_IntToString(i.index));
		FItemStruct* _itemStruct = nullptr;
		if (DataTable) _itemStruct = DataTable->FindRow<FItemStruct>(s, "", true);
		FRotator _tempRot = FRotator{0,0,0};
		FActorSpawnParameters spawnParams;
		
		if (_itemStruct)
		{
			TSubclassOf<AInteractableObject> _classToSpawn = _itemStruct->actorClass;
			GetWorld()->SpawnActor<AInteractableObject>(_classToSpawn, i.location, _tempRot, spawnParams);
		}
	}
}

