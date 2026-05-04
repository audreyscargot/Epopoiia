// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableAltar.h"

#include "Epopoiia/Core/GameInstanceMain.h"
#include "Kismet/KismetMathLibrary.h"

const int templeBaseMoney = 1000;

// Sets default values
AInteractableAltar::AInteractableAltar()
{
}

// Called when the game starts or when spawned
void AInteractableAltar::BeginPlay()
{
	Super::BeginPlay();
	gameInstance = Cast<UGameInstanceMain>(GetGameInstance());
	if (gameInstance)
	{
		hasBeenUsed = gameInstance->GetHasAltarBeenUsed();
		MakeMoney();
	}
}

void AInteractableAltar::Interact_Implementation(APlayerCharacter* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
	if (isFixed)
	{
		if (!hasBeenUsed && gameInstance)
		{
			hasBeenUsed = true;
			gameInstance->SetHasAltarBeenUsed(true);
			gameInstance->SetPlayerMoney(currentMoney);
		}
	}
}

void AInteractableAltar::MakeMoney()
{
	int _multiplier = UKismetMathLibrary::FCeil(gameInstance->GetReviewGrade()/5);
	currentMoney = _multiplier * templeBaseMoney;
}
