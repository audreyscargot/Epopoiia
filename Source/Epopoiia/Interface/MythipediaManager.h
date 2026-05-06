// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Epopoiia/Core/ItemStruct.h"
#include "MythipediaManager.generated.h"

enum class ESpirit : uint8;

USTRUCT(BlueprintType)
struct FAvailableVocabularyMap
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	EVocabularyType Type;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<FString> Sentences;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EPOPOIIA_API UMythipediaManager : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<FMythipediaPost> allPosts;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TMap<FString, EVocabularyType> vocabulary;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<FAvailableVocabularyMap> sentencesMap;
	

public:
	// Sets default values for this component's properties
	UMythipediaManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	TMap<FString, EVocabularyType> GetVocabulary();
	virtual void SetVocabulary(TMap<FString, EVocabularyType> _vocabulary);
	
	TArray<FMythipediaPost> GetAllPosts();
	virtual void SetAllPosts(TArray<FMythipediaPost> _allPosts);
	
	UFUNCTION(BlueprintCallable)
	virtual void AddToVocabulary(FString _word, EVocabularyType _type);
	
	UFUNCTION(BlueprintCallable)
	virtual void AddPost(FMythipediaPost _newPost);
	
};
