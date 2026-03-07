// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableNPC.h"

#include "PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"

AInteractableNPC::AInteractableNPC()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(RootComponent);
	regularRotator = GetActorRotation();
}

void AInteractableNPC::Interact_Implementation(APlayerCharacter* InstigatorPawn)
{
	if (!isInteracted)
	{
		isInteracted = true;
	}
	else
	{
		if (interactWidgetRef)
		{
			interactWidgetRef->RemoveFromParent();
			interactWidgetRef = nullptr;
		}
		isInteracted = false;
	}
	SetDialogueView(InstigatorPawn);
}


void AInteractableNPC::SetDialogueView(APlayerCharacter* InstigatorPawn)
{
	//Set view and Widget TO DO
	UE_LOG(LogTemp, Warning, TEXT("%hhd"), isInteracted);
	FTransform _transform = isInteracted ? cameraInteractTransform : InstigatorPawn->GetCameraRegularTransform();
	float _targetArmLength = isInteracted ? interactTargetArmLength : InstigatorPawn->GetRegularTargetArmLength();
	InstigatorPawn->SetCameraView(false, _transform, _targetArmLength );
	InstigatorPawn->SetCanLookMove(!isInteracted);
	
	//Turn Character to face Player
	FRotator _newRotation = isInteracted ? UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), InstigatorPawn->GetActorLocation()) : regularRotator;
	SetActorRotation(FRotator(0, _newRotation.Yaw, 0));
}

void AInteractableNPC::Thinking()
{
	
}

void AInteractableNPC::Dialogue()
{
	
}
