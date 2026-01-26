// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class EPOPOIIA_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public : 
	AMyPlayerController();
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TArray<UInputMappingContext*> InputMapping;
	
protected:
	virtual void SetupInputComponent() override;
	
};
