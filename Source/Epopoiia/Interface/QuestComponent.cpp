// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"

#include "Kismet/KismetMathLibrary.h"

const int progressWhenFinished = 1;

UQuestComponent::UQuestComponent()
{
	
}


void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	gameInstance = Cast<UGameInstanceMain>(GetWorld()->GetGameInstance());
	owner = Cast<AInteractableNPC>(GetOwner());
	if (owner)
	{
		ownerID = owner->GetNPCID();
	}
	CheckQuestSaved();
}

void UQuestComponent::CheckQuestSaved()
{
	if (gameInstance)
	{
		TArray<FNPCsQuest> _quests = gameInstance->GetQuestsOfDay();
		UE_LOG(LogTemp, Warning, TEXT("saved quest quantity : %i"), _quests.Num());
		for (auto _quest : _quests)
		{
			UE_LOG(LogTemp, Warning, TEXT("quest check, ID == owner ID ? %hs"), _quest.npcID == owner->GetNPCID() ? "true" : "false");
			if (_quest.npcID == ownerID)
			{
				LoadQuests(_quest);
				return;
			}
		}
		CreateQuests();
	}
}

void UQuestComponent::LoadQuests(FNPCsQuest _quest)
{
	NPCquest = _quest;
}

void UQuestComponent::CreateQuests()
{
	UE_LOG(LogTemp, Warning, TEXT("CreateQuests"));
	int _randQuestQuantity = FMath::RandRange(2, 3);
	int _seed = 0;
	NPCquest.questDialogueNPC.SetNum(_randQuestQuantity);
	
	NPCquest.npcID = owner->GetNPCID();
	
	for (int i = 0; i < _randQuestQuantity; i++)
	{
		if (availableQuests)
		{
			_seed = gameInstance->GetSeed()*100 + NPCquest.npcID*10 + i;
			TArray<FName> _questNames = availableQuests->GetRowNames();
			FMath::SRandInit(_seed);
			int questID = FMath::RandRange(0, _questNames.Num() - 1);
			FName _questName = _questNames[questID];
			NPCquest.quest.Add(_questName);
			NPCquest.currentQuestIndex = 0;
			FQuestDialogueNPC _questDialogueNPC = FQuestDialogueNPC(_questName, {});
			NPCquest.questDialogueNPC.Add(_questDialogueNPC);
			MakeDialogues(i);
		}
	}
	SetQuests();
}

void UQuestComponent::MakeDialogues(int _questIndex)
{
	TArray<int> _allIndex;
	TArray<FString> _questDialogue = availableQuests->FindRow<FQuestsInfo>(NPCquest.quest[NPCquest.currentQuestIndex], "", true)->DialogueSentences;
	for (int i = 0; i < _questDialogue.Num(); i++) //creates array of all dialogue index (0,1,2..)
	{
		_allIndex.Add(i);
	}
	for (int i = 0; i < 2; i++)
	{
		int _index = _allIndex[UKismetMathLibrary::RandomIntegerInRange(0, _allIndex.Num()-1)]; //pick value at random index and stores value
		NPCquest.questDialogueNPC[_questIndex].questDialogueIndex.Add(_index);
		_allIndex.Remove(_index);
	}
}

void UQuestComponent::FinishQuest(bool _isGoodAnswer)
{
	if (NPCquest.quest.IsValidIndex(NPCquest.currentQuestIndex))
	{
		NPCquest.currentQuestIndex++;
		if (_isGoodAnswer && owner)
		{
			owner->GetActivePlayer()->UpdateTimeRewindAbility(progressWhenFinished);
		}
		gameInstance->UpdateQuestsOfDay(NPCquest);
	}
}

void UQuestComponent::SetQuests()
{
	gameInstance->AddQuestsOfDay(NPCquest);
	gameInstance->SaveQuests();
	gameInstance->SaveGameToSlot();
}


