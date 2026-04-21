// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Epopoiia/Player/PlayerCharacter.h"
#include "GameInstanceMain.generated.h"

class AInteractableObject;
class USaveGameEpopoiia;
//struct to register all elements placed in temples and if they are fixed
USTRUCT(BlueprintType)
struct FFurnitureState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | Temple")
	int index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | Temple")
	FVector location;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | Temple")
	FTransform transform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | Temple")
	bool isFixed;
};

USTRUCT(BlueprintType)
struct FShopState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | ShopState")
	int index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | ShopState")
	bool state;
};

USTRUCT(BlueprintType)
struct FNPCsQuest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | NPCQuest")
	int npcID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save | NPCQuest")
	TArray<FName> quest; //int -> quests ID, bool -> isQuestFinished ?
};

UCLASS()
class EPOPOIIA_API UGameInstanceMain : public UGameInstance
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
	APlayerCharacter* player;
	
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
	
public :
	virtual void Init() override;
	
	TArray<FFurnitureState> GetTempleState();
	
	TMap<int, bool> GetTempleFixedState();
	
	int GetSeed();
	void SetSeed(int _newSeed);
	
	TArray<FNPCsQuest> GetQuestsOfDay();
	void AddQuestsOfDay(FNPCsQuest _quest);
	void UpdateQuestsOfDay(FNPCsQuest _quest);
	
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
	
	UFUNCTION()
	virtual void ResetGameInstance();
	
	UFUNCTION()
	virtual void setSavedVariables();
	
};
