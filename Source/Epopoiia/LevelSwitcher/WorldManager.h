// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldManager.generated.h"

class AFixableObject;
struct FItemStruct;
class AInteractableObject;
struct FFurnitureState;
class UGameInstanceMain;

UCLASS()
class EPOPOIIA_API AWorldManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWorldManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UGameInstanceMain* GameInstance;
	
	UPROPERTY()
	TArray<FFurnitureState> WorldState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DataTable;

public:
	
	UFUNCTION()
	virtual void ManageWorld();
	
	UFUNCTION()
	virtual void FixFurniture(AFixableObject* _obj, bool _isFixed);
	
	UFUNCTION()
	virtual void FixTempleState();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateTempleState(bool _isDay);
};
