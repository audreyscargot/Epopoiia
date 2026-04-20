// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.h"
#include "GameFramework/GameModeBase.h"
#include "Spatial/DenseGrid2.h"
#include "EpopoiiaGameMode.generated.h"

class APlayerCharacter;


UCLASS()
class EPOPOIIA_API AEpopoiiaGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	AEpopoiiaGameMode();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UDataTable* AvailableItems;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<FVector> Grid;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int gridMaxX;

public:
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int gridMinX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int gridMaxY;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int gridMinY;
	
	// TMap<FVector, bool> Grid2

public:
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	int GetGridMaxX() const;
	
	UFUNCTION()
	int GetGridMaxY() const;
	
	UFUNCTION()
	int GetGridMinX() const;
	
	UFUNCTION()
	int GetGridMinY() const;
	
	UFUNCTION()
	virtual void CreateGrid(int _width, int _depth);
	
	UFUNCTION()
	virtual void UseObject(int itemID);
	
	UFUNCTION()
	virtual void SpawnObject(FItemStruct& _itemInfo);
	
	UFUNCTION()
	virtual void makeSeed();

	UFUNCTION()
	UDataTable* GetAvailableItems();
};
