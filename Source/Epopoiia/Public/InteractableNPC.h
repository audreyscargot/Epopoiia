// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "InteractableNPC.generated.h"

/**
 * 
 */
UCLASS()
class EPOPOIIA_API AInteractableNPC : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	void Interact_Implementation(APlayerCharacter* InstigatorPawn) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Dialogue();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Thinking();
};
