// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"

#include "DetectUserWidget.h"
#include "Components/WidgetComponent.h"
#include "InteractInterface.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(RootComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->SetBoxExtent(Mesh->Bounds.BoxExtent, false);
	BoxComponent->SetWorldRotation(FRotator(0, 0, 0));
	
	//Make all pushing/pulling points
	InteractPoints[0] = (MakeInteractPoints(-BoxComponent->GetRightVector())); //left
	InteractPoints[1] = (MakeInteractPoints(BoxComponent->GetRightVector())); //right
	InteractPoints[2] = (MakeInteractPoints(-BoxComponent->GetForwardVector())); //back
	InteractPoints[3] = (MakeInteractPoints(BoxComponent->GetForwardVector())); //front
}

void AInteractableObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	BoxComponent->SetRelativeLocation(FVector(0, 0, BoxComponent->Bounds.BoxExtent.Z));
}

FVector AInteractableObject::MakeInteractPoints(FVector _direction)
{
	FVector InteractPoint;
	float value = 50.0;
	InteractPoint.X = (_direction * value).X;
	InteractPoint.Y = (_direction * value).Y;
	InteractPoint.Z = -BoxComponent->Bounds.BoxExtent.Z;
	return InteractPoint;
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Interacttion System w/ feedback
void AInteractableObject::Interact_Implementation(APlayerCharacter* InstigatorPawn)
{
	
}

void AInteractableObject::CanBeInteracted_Implementation()
{
	if (bIsInteractable && !InteractWidget->IsVisible())
	{
		InteractWidget->SetVisibility(true);
		FeedbackWidgetAppear();
	}
}

void AInteractableObject::RemoveInteractFeedback_Implementation()
{
	if (InteractWidget->IsVisible())
	{
		InteractWidget->SetVisibility(false);
	}
	
}

void AInteractableObject::FeedbackWidgetAppear()
{
	if (UDetectUserWidget* DetectWidget = Cast<UDetectUserWidget>(InteractWidget->GetWidget())) DetectWidget->MakeDetectionAppear();
}




