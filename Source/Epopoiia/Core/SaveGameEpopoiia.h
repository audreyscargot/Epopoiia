// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameInstanceMain.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameEpopoiia.generated.h"


UCLASS()
class EPOPOIIA_API USaveGameEpopoiia : public USaveGame
{
	GENERATED_BODY()
	
	protected:
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FFurnitureState> templeState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TMap<int, bool> templeFixedState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<int> playerInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int seed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FShopState> shopState;;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	USaveGameEpopoiia* currentSaveGame;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FNPCsQuest> questsOfDay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int playerTimeRewindAbilityLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	bool hasAltarBeenUsed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int templeReviewGrade;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int playerMoney;
	
public:
	
	TArray<FFurnitureState> GetTempleState();
	void SetTempleState(TArray<FFurnitureState> _templeState);
	
	TMap<int, bool> GetFixedState();
	void SetFixedState(TMap<int, bool> _fixedState);
	
	TArray<int> GetPlayerInventory();
	void SetPlayerInventory(TArray<int> _playerInventory);
	
	int GetSeed();
	void SetSeed(int _seed);
	
	TArray<FShopState> GetShopState();
	void SetShopState(TArray<FShopState> _shopState);
	
	TArray<FNPCsQuest> GetQuests();
	void SetQuests(TArray<FNPCsQuest> _quests);
	
	bool GetHasAltarBeenUsed();
	void SetHasAltarBeenUsed(bool _hasAltarBeenUsed);
	
	int GetTempleReviewGrade();
	void SetTempleReviewGrade(int _templeReviewGrade);
	
	int GetPlayerMoney();
	void SetPlayerMoney(int _playerMoney);
	
	int GetPlayerTimeRewindAbility();
	void SetPlayerTimeRewindAbility(int _playerTimeRewindAbility);
};
