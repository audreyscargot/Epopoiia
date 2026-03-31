// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.h"
#include "GameFramework/GameModeBase.h"
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

public:
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void CreateGrid(int _width, int _depth);
	
	UFUNCTION()
	virtual void UseObject(int itemID);
	
	UFUNCTION()
	virtual void SpawnObject(FItemStruct& _itemInfo);
};
