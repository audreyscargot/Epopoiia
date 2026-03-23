// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:
	
	UFUNCTION()
	virtual void UseObject(int itemID);
};
