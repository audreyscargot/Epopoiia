// Fill out your copyright notice in the Description page of Project Settings.


#include "FixableAltar.h"

#include "Epopoiia/Core/GameInstanceMain.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

const int templeBaseMoney = 100;

// Sets default values
AFixableAltar::AFixableAltar()
{
	OfferingMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	OfferingMesh->SetupAttachment(RootComponent);
}


void AFixableAltar::BeginPlay()
{
	Super::BeginPlay();
	gameInstance = Cast<UGameInstanceMain>(GetGameInstance());
	if (gameInstance)
	{
		hasBeenUsed = gameInstance->GetHasAltarBeenUsed();
		MakeMoney();
	}
	SetOfferingVisibility(!hasBeenUsed && isFixed);
	
}

void AFixableAltar::Interact_Implementation(APlayerCharacter* InstigatorPawn)
{
	if (isFixed)
	{
		if (!hasBeenUsed && gameInstance)
		{
			hasBeenUsed = true;
			gameInstance->SetHasAltarBeenUsed(true);
			gameInstance->SetPlayerMoney(currentMoney);
			SetOfferingVisibility(false);
		}
	}
	Super::Interact_Implementation(InstigatorPawn);
}

void AFixableAltar::MakeMoney()
{
	int _multiplier = UKismetMathLibrary::FCeil(gameInstance->GetReviewGrade()/5);
	currentMoney = _multiplier * templeBaseMoney;
}

void AFixableAltar::SetOfferingVisibility(bool _shouldBeVisible)
{
	SetOfferingLocation();
	OfferingMesh->SetVisibility(_shouldBeVisible);
}

void AFixableAltar::SetOfferingLocation()
{
	FVector _origin;
	FVector _boxExtent;
	float _radius;
	UKismetSystemLibrary::GetComponentBounds(GetMesh(), _origin, _boxExtent, _radius);
	OfferingMesh->SetRelativeLocation(FVector(0,0,_origin.Z + _boxExtent.Z));
}


