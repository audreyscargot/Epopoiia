// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Epopoiia/Player/PlayerCharacter.h"
#include "GameInstanceMain.generated.h"

class USaveGameEpopoiia;
//struct to register all elements placed in temples and if they are fixed
USTRUCT(BlueprintType)
struct FFurnitureState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FVector location;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	bool isFixed;
	
	
};

USTRUCT(BlueprintType)
struct FShopState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	bool state;
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
	TArray<int> playerInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	int seed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FShopState> shopState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	USaveGameEpopoiia* currentSaveGame;
	
public :
	virtual void Init() override;
	
	TArray<FFurnitureState> GetTempleState();
	void SetTempleState(TArray<FFurnitureState> templeState);
	
	int GetSeed();
	void SetSeed(int _newSeed);
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveInventory();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveSeed();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveShopState();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveTemple();
	
	UFUNCTION(BlueprintCallable)
	virtual void SaveGeneral();
	
};
