// Fill out your copyright notice in the Description page of Project Settings.


#include "FixableObject.h"

#include "PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"

AFixableObject::AFixableObject()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}


void AFixableObject::Interact_Implementation(APlayerCharacter* InstigatorPawn)
{
	if (InstigatorPawn->GetTimeRewindAbilityLevel() >= RequiredLevel)
	{
		Repair();
	}
}

void AFixableObject::Repair()
{
	UE_LOG(LogTemp, Warning, TEXT("Fixing !"))
}
