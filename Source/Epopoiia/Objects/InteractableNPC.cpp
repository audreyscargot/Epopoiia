// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableNPC.h"

#include "Epopoiia/Player/PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Epopoiia/Interface/QuestComponent.h"
#include "Kismet/BlueprintMapLibrary.h"
#include "Kismet/KismetMathLibrary.h"

AInteractableNPC::AInteractableNPC()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(RootComponent);
	regularRotator = GetActorRotation();
	QuestComponent = CreateDefaultSubobject<UQuestComponent>("QuestComponent");
}

void AInteractableNPC::Interact_Implementation(APlayerCharacter* InstigatorPawn)
{
	if (GameInstance->GetQuestsOfDay()[npcID].quest.IsValidIndex(GameInstance->GetQuestsOfDay()[npcID].currentQuestIndex))
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
		activePlayer = InstigatorPawn;
	}
}

void AInteractableNPC::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UGameInstanceMain>(GetWorld()->GetGameInstance());
}

int AInteractableNPC::GetNPCID()
{
	return npcID;
}

APlayerCharacter* AInteractableNPC::GetActivePlayer()
{
	return activePlayer;
}

//----------------DIALOGUE FUNCTIONS----------------------

void AInteractableNPC::SetDialogueView(APlayerCharacter* InstigatorPawn)
{
	//Set view and Widget TODO
	UE_LOG(LogTemp, Warning, TEXT("%hhd"), isInteracted);
	FVector _locationToLookAt = (InstigatorPawn->GetActorLocation()+GetActorLocation())/2;
	
	FVector _location = InstigatorPawn->GetActorLocation()+_locationToLookAt;
	cameraInteractTransform.SetLocation(_location);
	
	FRotator _rotation = UKismetMathLibrary::FindLookAtRotation(cameraInteractTransform.GetLocation(), InstigatorPawn->GetCameraRegularTransform().GetLocation());
	cameraInteractTransform.SetRotation(_rotation.Quaternion());
	
	FTransform _transform = isInteracted ? cameraInteractTransform : InstigatorPawn->GetCameraRegularTransform();
	float _targetArmLength = isInteracted ? interactTargetArmLength : InstigatorPawn->GetRegularTargetArmLength();
	InstigatorPawn->SetCameraView(false, _transform, _targetArmLength );
	InstigatorPawn->SetCanLookMove(!isInteracted);
	
	//Turn Character to face Player
	FRotator _newRotation = isInteracted ? UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), InstigatorPawn->GetActorLocation()) : regularRotator;
	SetActorRotation(FRotator(0, _newRotation.Yaw, 0));
}
