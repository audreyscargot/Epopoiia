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
		if (GameInstance->GetQuestsOfDay().IsValidIndex(npcID)) //if quests are already saved in GameInstance, use the saved ones
		{
			TArray<FNPCsQuest> _tempQuest = GameInstance->GetQuestsOfDay();
			Quests = _tempQuest[npcID];
			currentQuestIndex = _tempQuest[npcID].currentQuestIndex;
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
	
	Quests.npcID = npcID;
	
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
			AssignDialogueIndex();
			Quests.questDialogueNPC.Add(FQuestDialogueNPC(QuestName, dialogueIndex));
		}
	}
	GameInstance->AddQuestsOfDay(Quests);
	currentQuestIndex = 0;
	SetActiveQuest();
}

void AInteractableNPC::SetActiveQuest()
{
	if (Quests.quest[currentQuestIndex].IsValid())
	{
		activeQuest = Quests.quest[currentQuestIndex];
	}
}

void AInteractableNPC::FinishQuest()
{
	if (Quests.quest[currentQuestIndex].IsValid())
	{
		currentQuestIndex++;
		GameInstance->GetQuestsOfDay()[npcID].currentQuestIndex = currentQuestIndex;
		SetActiveQuest(); //TODO : set new quest at random day time instead of right after completion
	}
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

void AInteractableNPC::AssignDialogueIndex()
{
	if (GameInstance && !Quests.quest.IsEmpty())
	{
		dialogueIndex.Empty();
		TArray<FString> QuestNames = availableQuests->FindRow<FQuestsInfo>(Quests.quest[0], "", true)->DialogueSentences;
		for (int i = 0; i < 2; i++)
		{
			int _index = FMath::Rand() % QuestNames.Num();
			dialogueIndex.Add(_index);
			if (QuestNames.IsValidIndex(_index))
			{
				QuestNames.RemoveAt(_index, EAllowShrinking::Yes);
			}
		}
	}
}

void AInteractableNPC::Thinking()
{
	
}
