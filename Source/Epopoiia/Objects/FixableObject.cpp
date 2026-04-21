// Fill out your copyright notice in the Description page of Project Settings.


#include "FixableObject.h"

#include "Epopoiia/Player/PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

AFixableObject::AFixableObject()
{
	
}

void AFixableObject::BeginPlay()
{
	Super::BeginPlay();
	if (isFixed) SetMesh(itemInfo.FixedMesh);
}

void AFixableObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AFixableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AFixableObject::Interact_Implementation(APlayerCharacter* InstigatorPawn)
{
	if (InstigatorPawn->GetTimeRewindAbilityLevel() >= RequiredLevel && bIsInteractable)
	{
		Repair();
	}
}

void AFixableObject::CanBeInteracted_Implementation()
{
	Super::CanBeInteracted_Implementation();
}

void AFixableObject::RemoveInteractFeedback_Implementation()
{
	Super::RemoveInteractFeedback_Implementation();
}

//Repair To do : add Niagara feedback
void AFixableObject::Repair()
{
	bIsInteractable = false;
	isFixed = true;
	InteractWidget->SetVisibility(false);
	UE_LOG(LogTemp, Warning, TEXT("Fixing !"))
	Mesh->SetStaticMesh(itemInfo.FixedMesh);
	
}

void AFixableObject::MakeMesh()
{
	FName _row = FName(FString::FromInt(ID));
	FString _context = "";
	if (!DataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable null"));
		return;
	}
	FItemStruct* _itemInfo = DataTable->FindRow<FItemStruct>(_row, _context, true);
	if (_itemInfo)
	{
		SetMesh(isFixed ? _itemInfo->FixedMesh : _itemInfo->Mesh);
	}
}
