// Fill out your copyright notice in the Description page of Project Settings.


#include "FixableObject.h"

#include "K2Node_GetClassDefaults.h"
#include "PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

AFixableObject::AFixableObject()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}


void AFixableObject::Interact_Implementation(APlayerCharacter* InstigatorPawn)
{
	if (InstigatorPawn->GetTimeRewindAbilityLevel() >= RequiredLevel && bIsInteractable)
	{
		Repair();
	}
}

//Repair To do : add Niagara feedback
void AFixableObject::Repair()
{
	bIsInteractable = false;
	InteractWidget->SetVisibility(false);
	UE_LOG(LogTemp, Warning, TEXT("Fixing !"))
	Mesh->SetStaticMesh(RepairedMesh);
	
}
