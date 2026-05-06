// Fill out your copyright notice in the Description page of Project Settings.


#include "MythipediaManager.h"


// Sets default values for this component's properties
UMythipediaManager::UMythipediaManager()
{
	
}


void UMythipediaManager::BeginPlay()
{
	
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
}



