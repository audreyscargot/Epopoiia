// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Epopoiia/Player/PlayerCharacter.h"
#include "GameInstanceMain.generated.h"

enum class EVocabularyType : uint8;
struct FMythipediaPost;
struct FReviewStruct;
struct FReviewBaseStruct;
class UReviewManagerComponent;
class AInteractableShop;
class AInteractableObject;
class USaveGameEpopoiia;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSuccessfullyBought, int, _shopSlot);

//struct to register all elements placed in temples and if they are fixed
USTRUCT(BlueprintType)
struct FFurnitureState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | Temple")
	int index = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | Temple")
	FVector location = FVector(0, 0, 0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | Temple")
	FTransform transform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | Temple")
	bool isFixed = false;
};

USTRUCT(BlueprintType)
struct FShopState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | ShopState")
	FName index = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | ShopState")
	bool hasBeenBought = false;
};

USTRUCT(BlueprintType)
struct FQuestDialogueNPC // to store dialogue lines index to only use the same ones everytime player talks with NPC
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | QuestDialogue")
	FName questName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | QuestDialogue")
	TArray<int> questDialogueIndex;
};

USTRUCT(BlueprintType)
struct FNPCsQuest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | NPCQuest")
	int npcID = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | NPCQuest")
	TArray<FName> quest;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | NPCQuest")
	TArray<FQuestDialogueNPC> questDialogueNPC;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | NPCQuest")
	int currentQuestIndex = 0;
};

UCLASS()
class EPOPOIIA_API UGameInstanceMain : public UGameInstance
{
	GENERATED_BODY()
	
	protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FFurnitureState> TempleState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TMap<int, bool> TempleFixedState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<int> playerInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int seed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FShopState> shopState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	USaveGameEpopoiia* currentSaveGame;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FNPCsQuest> questsOfDay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int templeLevel = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int playerTimeRewindAbilityLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	bool hasAltarBeenUsed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int templeReviewGrade = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FReviewStruct> reviews;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int playerMoney;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FMythipediaPost> playerPosts;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TMap<FString, EVocabularyType> playerVocabulary;
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
	FSuccessfullyBought SuccessfullyBoughtDelegate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
	APlayerCharacter* player;
	
	virtual void Init() override;
	
	TArray<FFurnitureState> GetTempleState();
	
	TMap<int, bool> GetTempleFixedState();
	
	int GetSeed();
	void SetSeed(int _newSeed);
	
	int GetTimeRewindAbility();
	void SetTimeRewindAbility(int _toAdd);
	
	bool GetHasAltarBeenUsed();
	void SetHasAltarBeenUsed(bool _hasAltarBeenUsed);
	
	int GetReviewGrade();
	void SetReviewGrade(int _reviewGrade);
	
	TArray<FReviewStruct> GetReviews();
	void SetReviews(TArray<FReviewStruct> _reviews);
	
	int GetPlayerMoney();
	void SetPlayerMoney(int _playerMoney);
	
	TArray<int> GetPlayerInventory();
	
	TArray<FMythipediaPost> GetPlayerPosts();
	virtual void SetPlayerPosts(TArray<FMythipediaPost> _playerPosts);
	
	TMap<FString, EVocabularyType> GetPlayerVocabulary();
	virtual void SetPlayerVocabulary(TMap<FString, EVocabularyType> _vocabulary);
	
	TArray<FShopState> GetShopState();
	void SetShopState(TArray<FShopState> _shopState);
	
	TArray<FNPCsQuest> GetQuestsOfDay();
	void AddQuestsOfDay(FNPCsQuest _quest);
	void UpdateQuestsOfDay(FNPCsQuest _quest);
	
	UFUNCTION(BlueprintCallable)
	void BuyObject(int _price, int _objectID, int _shopSlot);
	
	UFUNCTION(BlueprintCallable)
	void UpdateGIInventory(UInventoryComponent* _inventory);
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveInventory();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveSeed();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveShopState();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveTemple();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveFixedTemple(TArray<AInteractableObject*> _registeredActors);
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveQuests();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveGeneral();
	
	UFUNCTION(BlueprintCallable)
	virtual void SavePlayerTimeRewindAbility();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveAltar();
	
	virtual void SavePlayerMoney();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveReviews();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveReviewGrade();
	
	UFUNCTION(BlueprintCallable)
	virtual void SavePlayerVocabulary();
	
	UFUNCTION(BlueprintCallable)
	virtual void SavePosts();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveGameToSlot();
	
	UFUNCTION()
	virtual void ResetGameInstance();
	
	UFUNCTION()
	virtual void setSavedVariables();
	
	UFUNCTION()
	virtual void InitVariables();
	
};
