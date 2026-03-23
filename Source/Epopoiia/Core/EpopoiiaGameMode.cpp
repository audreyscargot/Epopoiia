// Fill out your copyright notice in the Description page of Project Settings.


#include "EpopoiiaGameMode.h"

#include "ItemStruct.h"
#include "Epopoiia/Objects/InteractableObject.h"

AEpopoiiaGameMode::AEpopoiiaGameMode()
{
	
}

void AEpopoiiaGameMode::UseObject(int itemID)
{
	//Get data from DT row
	FName _row = FName(FString::FromInt(itemID));
	FString _context = "";
	FItemStruct* _itemProperty = new FItemStruct();
	if (AvailableItems) _itemProperty = AvailableItems->FindRow<FItemStruct>(_row, _context , true);
	
	//execute use object (currently spawn only)
	if (_itemProperty)
	{
		//make Parameters
		AActor* _player = GetWorld()->GetFirstPlayerController()->GetPawn(); 
		
		float _size = _itemProperty->Mesh->GetBounds().BoxExtent.X;
		FVector _location = _player->GetActorLocation() + _player->GetActorForwardVector()*(_size + 30);
		FRotator _rotation = FRotator(0, 0, 0);
		FActorSpawnParameters _spawnParams;
		TSubclassOf<AInteractableObject> _classToSpawn = _itemProperty->actorClass;
		if (_classToSpawn) GetWorld()->SpawnActor<AInteractableObject>(_classToSpawn, _location, _rotation, _spawnParams);
		
		//TODO : add if more variations
	}
}
