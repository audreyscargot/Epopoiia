// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceMain.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameEpopoiia.h"
#include "Kismet/GameplayStatics.h"

const FString saveName = FString("EpopoiiaSave");
const TSubclassOf<USaveGameEpopoiia> saveGameClass;

void UGameInstanceMain::Init()
{
	Super::Init();
	bool isSaveGameValid;
	isSaveGameValid = UGameplayStatics::DoesSaveGameExist(saveName, 0);
	if (!isSaveGameValid)
	{
		currentSaveGame = Cast<USaveGameEpopoiia>(UGameplayStatics::CreateSaveGameObject(saveGameClass));
		UGameplayStatics::SaveGameToSlot(currentSaveGame, saveName, 0);
	}
	else
	{
		currentSaveGame = Cast<USaveGameEpopoiia>(UGameplayStatics::LoadGameFromSlot(saveName, 0));
	} 
}

void UGameInstanceMain::SaveAll()
{
	
}
