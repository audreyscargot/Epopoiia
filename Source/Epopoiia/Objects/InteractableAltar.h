// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FixableObject.h"
#include "InteractableObject.h"
#include "InteractableAltar.generated.h"

class UGameInstanceMain;

UCLASS()
class EPOPOIIA_API AInteractableAltar : public AFixableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableAltar();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameInstanceMain* gameInstance; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Properties")
	int currentMoney = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Properties")
	bool hasBeenUsed = false;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Interact_Implementation(APlayerCharacter* InstigatorPawn) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void MakeMoney();
};
