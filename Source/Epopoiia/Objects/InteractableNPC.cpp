// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableNPC.h"

#include "Epopoiia/Player/PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/BlueprintMapLibrary.h"
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

void AInteractableNPC::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UGameInstanceMain>(GetWorld()->GetGameInstance());
	MakeQuests();
}

//----------------QUEST FUNCTIONS----------------------

void AInteractableNPC::MakeQuests()
{
	if (GameInstance)
	{
		if (GameInstance->GetQuestsOfDay().IsValidIndex(ID)) //if quests are already saved in GameInstance, use the saved ones
		{
			TArray<FNPCsQuest> _tempQuest = GameInstance->GetQuestsOfDay();
			Quests = _tempQuest[npcID];
		}
		else
		{
			AssignQuests();
		}
	}
}

void AInteractableNPC::AssignQuests()
{
	int randQuestQuantity = FMath::RandRange(1, 2);
	int _seed = 0;
	
	for (int i = 0; i < randQuestQuantity; i++)
	{
		if (availableQuests)
		{
			_seed = GameInstance->GetSeed()*100 + npcID*10 + i; //multiply by hundred to get unique seed for NPC quests (adding NPC ID*10 + quest number(0 to last quest index)
			TArray<FName> QuestNames = availableQuests->GetRowNames();
			FMath::SRandInit(_seed);
			int questID = FMath::SRand() * 100;
			questID = questID % QuestNames.Num();
			FName QuestName = QuestNames[questID];
			Quests.quest.Add(QuestName);
		}
	}
	GameInstance->AddQuestsOfDay(Quests);
}

void AInteractableNPC::SetActiveQuest()
{
	if (Quests.quest[0].IsValid()) activeQuest = Quests.quest[0];
}

void AInteractableNPC::FinishQuest()
{
	if (Quests.quest[0].IsValid()) Quests.quest.RemoveAt(0, EAllowShrinking::Yes);
}


//----------------DIALOGUE FUNCTIONS----------------------

void AInteractableNPC::SetDialogueView(APlayerCharacter* InstigatorPawn)
{
	//Set view and Widget TODO
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
