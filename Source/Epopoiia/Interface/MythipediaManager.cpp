// Fill out your copyright notice in the Description page of Project Settings.


#include "MythipediaManager.h"

#include "Epopoiia/Core/GameInstanceMain.h"


// Sets default values for this component's properties
UMythipediaManager::UMythipediaManager()
{
	
}


void UMythipediaManager::BeginPlay()
{
	Super::BeginPlay();
	gameInstance = Cast<UGameInstanceMain>(GetWorld()->GetGameInstance());
	if (gameInstance)
	{
		vocabulary = gameInstance->GetPlayerVocabulary();
	}
}

TMap<FString, EVocabularyType> UMythipediaManager::GetVocabulary()
{
	return vocabulary;
}

void UMythipediaManager::SetVocabulary(TMap<FString, EVocabularyType> _vocabulary)
{
	vocabulary = _vocabulary;
}

TArray<FMythipediaPost> UMythipediaManager::GetAllPosts()
{
	return allPosts;
}

void UMythipediaManager::SetAllPosts(TArray<FMythipediaPost> _allPosts)
{
	allPosts = _allPosts;
}

void UMythipediaManager::AddToVocabulary(FString _word, EVocabularyType _type)
{
	vocabulary.Add(_word, _type);
	gameInstance->SetPlayerVocabulary(vocabulary);
	gameInstance->SavePlayerVocabulary();
	
}

void UMythipediaManager::AddPost(FMythipediaPost _newPost)
{
	allPosts.Add(_newPost);
}

TMap<FString, FString> UMythipediaManager::GenerateAnswers(TArray<FString> _wordUsed)
{
	TMap<FString, FString> _postAnswers;
	int _randomIndex = FMath::RandRange(5, 10);
	
	if (_randomIndex < godUsernames.Num())
	{
		TArray<FString> _usernames = godUsernames;
		for (int i = 0; i < _randomIndex; i++)
		{
			int _randomUsernameIndex = FMath::RandRange(0, _usernames.Num() - 1);
			TPair<FString, FString> _comment;
			if (_usernames.IsValidIndex(_randomUsernameIndex))
			{
				FString _username = _usernames[_randomUsernameIndex];
				_usernames.RemoveAt(_randomUsernameIndex);
				_postAnswers.Add(_username, CreateAnswer(_wordUsed));
			}
		}
	}
	return _postAnswers;
}

FString UMythipediaManager::CreateAnswer(TArray<FString> _wordUsed)
{
	if (questInfos)
	{
		TArray<FQuestsInfo*> _allQuestsInfo;
		questInfos->GetAllRows<FQuestsInfo>("", _allQuestsInfo);
		int _highestIndex = 0;
		ESpirit _highestLikelySpirit = ESpirit::None;
		for (auto i : _allQuestsInfo)
		{
			int _questIndex = 0;
			ESpirit _currentSpirit = i->Spirit;
			for (auto j : i->learnedVocabulary)
			{
				if (_wordUsed.Contains(j.Key))
				{
					_questIndex++;
				}
			}
			if (_questIndex > _highestIndex)
			{
				_highestIndex = _questIndex;
				_highestLikelySpirit = _currentSpirit;
			}
		}
		FString _comment = commentSentences[FMath::RandRange(0, commentSentences.Num() - 1)] + UEnum::GetDisplayValueAsText(_highestLikelySpirit).ToString();
		return (_comment);
	}
	
	return FString("");
}



