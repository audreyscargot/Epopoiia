// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class EPOPOIIA_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Enhanced Input", meta = (AllowPrivateAccess))
	UInputMappingContext* InputMappingContext;
	
	virtual void SetupInputComponent() override;
};
