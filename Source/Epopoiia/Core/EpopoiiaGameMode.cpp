// Fill out your copyright notice in the Description page of Project Settings.


#include "EpopoiiaGameMode.h"

#include "GameInstanceMain.h"
#include "ItemStruct.h"
#include "Components/CapsuleComponent.h"
#include "Epopoiia/Objects/InteractableObject.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"

const int startingWidth = 15; //DO NOT USE ODD NUMBERS (for perfect middle)
const int startingDepth = 11;
const int cellSize = 150;

AEpopoiiaGameMode::AEpopoiiaGameMode()
{
	
}

void AEpopoiiaGameMode::BeginPlay()
{
	Super::BeginPlay();
	CreateGrid(startingWidth, startingDepth);
	makeSeed();
}

//Getters
int AEpopoiiaGameMode::GetGridMaxX() const
{
	return gridMaxX;
}

int AEpopoiiaGameMode::GetGridMaxY() const
{
	return gridMaxY;
}

int AEpopoiiaGameMode::GetGridMinX() const
{
	return gridMinX;
}

int AEpopoiiaGameMode::GetGridMinY() const
{
	return gridMinY;
}

//Grid For Spawners
void AEpopoiiaGameMode::CreateGrid(int _width, int _depth)
{
	// for (int i = 0; i < _depth; i++)
	// {
	// 	for (int j = 0; j < _width; j++)
	// 	{
	// 		int _newDepth = i * cellSize;
	// 		int _newWidth;
	// 		
	// 		//new width : if less than middle, -100; -200 etc/ if middle, 0 / if more, +100; +200
	// 		if (j < int32(_width/2)) _newWidth = (_width/2 - j) * -cellSize;
	// 		else if (j > int32(_width/2)) _newWidth = (j - _width/2) * cellSize;
	// 		else _newWidth = 0;
	// 		
	// 		FVector _newVector = FVector(_newDepth, _newWidth, 0);
	// 		Grid.Add(_newVector);
	// 	}
	// }
	
	gridMinX = 0;
	gridMinY = -_width * cellSize;
	gridMaxX = _depth * cellSize;
	gridMaxY = _width * cellSize;
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
	
	//choose Z for object on the ground depending on size
	int _Z = _location.Z - _player->GetCapsuleComponent()->GetLocalBounds().BoxExtent.Z + _itemInfo.Mesh->GetBounds().BoxExtent.Z;
	
	//Parameters useful for checking if spawnCell is empty
	FVector _spawnToCell;
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	//find closest cell in direction of player look	
	bool isLookingRight = UKismetMathLibrary::Abs(_player->GetActorForwardVector().X) < UKismetMathLibrary::Abs(_player->GetActorForwardVector().Y);
	UE_LOG(LogTemp, Warning, TEXT("isLookingRight: %d"), isLookingRight);
	if (isLookingRight)
	{
		FVector _playerCell = FVector (UKismetMathLibrary::GridSnap_Float(_location.X, cellSize), UKismetMathLibrary::FFloor(_location.Y / cellSize) * cellSize, _Z);
		int _spawnToY = _player->GetActorForwardVector().Y > 0 ? _playerCell.Y + cellSize : _playerCell.Y - cellSize;
		_spawnToCell = FVector (_playerCell.X, _spawnToY, _playerCell.Z);
		if (_spawnToY >= GetGridMinY() && _spawnToY <= GetGridMaxY()) //check if spawnable (in between grid availables cell)
		{
			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, _playerCell, _spawnToCell, ECC_Visibility, QueryParams);
			DrawDebugLine(GetWorld(), _playerCell, _spawnToCell, bHit ? FColor::Green : FColor::Red, false, 1.0f, 0, 1.0f);
			_canSpawn = !bHit;
		}
	}
	else
	{
		FVector _playerCell = FVector (UKismetMathLibrary::GridSnap_Float(_location.X, cellSize), UKismetMathLibrary::GridSnap_Float(_location.Y, cellSize), _Z);
		int _spawnToX = _player->GetActorForwardVector().X > 0 ? _playerCell.X + cellSize : _playerCell.X - cellSize;
		_spawnToCell = FVector (_spawnToX, _playerCell.Y, _playerCell.Z);
		if (_spawnToX >= GetGridMinX() && _spawnToX <= GetGridMaxX()) //check if spawnable (in between grid availables cell)
		{
			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, _playerCell, _spawnToCell, ECC_Visibility, QueryParams);
			_canSpawn = !bHit;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("spawn Cell %f, %f"), _spawnToCell.X, _spawnToCell.Y);
	FRotator _rotation = FRotator(0, 0, 0);
	FActorSpawnParameters _spawnParams;
	if (_classToSpawn && _canSpawn) GetWorld()->SpawnActor<AInteractableObject>(_classToSpawn, _spawnToCell, _rotation, _spawnParams);
}

void AEpopoiiaGameMode::makeSeed()
{
	FDateTime _now = UKismetMathLibrary::GetDate(UKismetMathLibrary::Now());
	FString _seed = FString::Printf(TEXT("%i%i%i") , _now.GetYear(), _now.GetMonth(), _now.GetDay());
	int _newSeed = UKismetStringLibrary::Conv_StringToInt(_seed);
	UGameInstanceMain* _GI = Cast<UGameInstanceMain>(GetGameInstance());
	if (_GI->GetSeed() != _newSeed)
	{
		_GI->SetSeed(_newSeed);
		UE_LOG(LogTemp, Warning, TEXT("New Seed: %i"), _GI->GetSeed());
	}
}
