// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "InteractableShop.generated.h"

struct FShopState;
class UGameInstanceMain;

UCLASS()
class EPOPOIIA_API AInteractableShop : public AInteractableObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* dtAvailableItems;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameInstanceMain* gameInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int shopSlotNumber = 5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FShopState> shopInventory;

public:
	// Sets default values for this actor's properties
	AInteractableShop();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Interact_Implementation(APlayerCharacter* InstigatorPawn) override;
	
	UFUNCTION()
	virtual void CheckIsShopSaved();
	
	UFUNCTION()
	virtual void MakeShop();
	
	UFUNCTION()
	virtual void LoadShop();
};
