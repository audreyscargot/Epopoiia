// Fill out your copyright notice in the Description page of Project Settings.


#include "FixableObject.h"

#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Epopoiia/Core/GameInstanceMain.h"

AFixableObject::AFixableObject()
{
	RepairedWidget = CreateDefaultSubobject<UWidgetComponent>("RepairedWidget");
	RepairedWidget->SetVisibility(false);
	RepairedWidget->SetWidgetSpace(EWidgetSpace::Screen);
	RepairedWidget->SetupAttachment(RootComponent);
}

void AFixableObject::BeginPlay()
{
	Super::BeginPlay();
	if (isFixed) SetMesh(itemInfo.FixedMesh);
	RepairedWidget->SetRelativeLocation(FVector(0.0f, 0.0f, (GetMesh()->Bounds.Origin.Z+GetMesh()->Bounds.BoxExtent.Z)/2));
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
	if (Cast<UGameInstanceMain>(GetWorld()->GetGameInstance())->GetTimeRewindAbility() >= RequiredLevel && bIsInteractable)
	{
		Repair();
	}
}

void AFixableObject::CanBeInteracted_Implementation()
{
	Super::CanBeInteracted_Implementation();
	if (!isFixed)
	{
		RepairedWidget->SetVisibility(true);
	}
}

void AFixableObject::RemoveInteractFeedback_Implementation()
{
	Super::RemoveInteractFeedback_Implementation();
	RepairedWidget->SetVisibility(false);
}

//Repair To do : add Niagara feedback
void AFixableObject::Repair()
{
	bIsInteractable = false;
	isFixed = true;
	InteractWidget->SetVisibility(false);
	UE_LOG(LogTemp, Warning, TEXT("Fixing !"))
	Mesh->SetStaticMesh(itemInfo.FixedMesh);
	RepairedWidget->SetVisibility(false);
	
}

void AFixableObject::MakeMesh()
{
	FName _row = FName(FString::FromInt(ID));
	FString _context = "";
	if (!DataTable)
	{
		return;
	}
	if (ID!=0)
	{
		FItemStruct* _itemInfo = DataTable->FindRow<FItemStruct>(_row, _context, true);
		if (_itemInfo)
		{
			SetMesh(isFixed ? _itemInfo->FixedMesh : _itemInfo->Mesh);
		}
	}
	
}
