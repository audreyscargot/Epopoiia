// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "Components/WidgetComponent.h"
#include "InteractInterface.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));

}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableObject::Interact_Implementation(APlayerCharacter* InstigatorPawn)
{
	
}

void AInteractableObject::CanBeInteracted_Implementation()
{
	InteractWidget->SetVisibility(true);
}

void AInteractableObject::RemoveInteractFeedback_Implementation()
{
	InteractWidget->SetVisibility(false);
}




