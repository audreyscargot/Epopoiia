// Fill out your copyright notice in the Description page of Project Settings.


#include "EpopoiiaGameMode.h"

#include "ItemStruct.h"
#include "Components/CapsuleComponent.h"
#include "Epopoiia/Objects/InteractableObject.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

const int startingWidth = 15; //DO NOT USE ODD NUMBERS (for perfect middle)
const int startingDepth = 11;
const int cellSize = 100;

AEpopoiiaGameMode::AEpopoiiaGameMode()
{
	
}

void AEpopoiiaGameMode::BeginPlay()
{
	Super::BeginPlay();
	CreateGrid(startingWidth, startingDepth);
}

//Grid For Spawners
void AEpopoiiaGameMode::CreateGrid(int _width, int _depth)
{
	for (int i = 0; i < _depth; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			int _newDepth = i * cellSize;
			int _newWidth;
			
			//new width : if less than middle, -100; -200 etc/ if middle, 0 / if more, +100; +200
			if (j < int32(_width/2)) _newWidth = (_width/2 - j) * -cellSize;
			else if (j > int32(_width/2)) _newWidth = (j - _width/2) * cellSize;
			else _newWidth = 0;
			
			FVector _newVector = FVector(_newDepth, _newWidth, 0);
			Grid.Add(_newVector);
		}
	}
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
		SpawnObject(*_itemProperty);
	}
	//TODO : add if more variations
}


void AEpopoiiaGameMode::SpawnObject(FItemStruct& _itemInfo)
{
	bool _canSpawn = false;
	
	//make Parameters
	ACharacter* _player = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()); 
	FVector _location = _player->GetActorLocation();
	
	float _size = _itemInfo.Mesh->GetBounds().BoxExtent.X;
	TSubclassOf<AInteractableObject> _classToSpawn = _itemInfo.actorClass;
	
	//place object on the ground depending on size
	int _Z = _location.Z - _player->GetCapsuleComponent()->GetLocalBounds().BoxExtent.Z + _itemInfo.Mesh->GetBounds().BoxExtent.Z;
	
	//make _playerCell to be closest cell, Z = future height for object spawned
	FVector _playerCell = FVector (UKismetMathLibrary::FFloor(_location.X / cellSize) * cellSize, UKismetMathLibrary::FFloor(_location.Y / cellSize) * cellSize, _Z);
	FVector _spawnToCell;
	
	//find closest cell in direction of player look	
	bool isLookingRight = _player->GetActorForwardVector().X < _player->GetActorForwardVector().Y ? true : false;
	if (isLookingRight)
	{
		int _spawnToY = _player->GetActorLocation().Y > 0 ? _playerCell.Y - cellSize : _playerCell.Y + cellSize;
		_spawnToCell = FVector (_playerCell.X, _spawnToY, _playerCell.Z);
		if (_spawnToY >= Grid[0].Y && _spawnToY <= Grid.Last().Y) //check if spawnable (in between grid availables cell)
		{
			_canSpawn = true;
		}
	}
	else
	{
		int _spawnToX = _player->GetActorLocation().X > 0 ? _playerCell.X - cellSize : _playerCell.X + cellSize;
		_spawnToCell = FVector (_spawnToX, _playerCell.Y, _playerCell.Z);
		if (_spawnToX >= Grid[0].Y && _spawnToX <= Grid.Last().Y) //check if spawnable (in between grid availables cell)
		{
			_canSpawn = true;
		}
	}
		
	FRotator _rotation = FRotator(0, 0, 0);
	FActorSpawnParameters _spawnParams;
	if (_classToSpawn && _canSpawn) GetWorld()->SpawnActor<AInteractableObject>(_classToSpawn, _spawnToCell, _rotation, _spawnParams);
}
