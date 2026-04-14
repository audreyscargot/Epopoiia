// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameEpopoiia.h"

TArray<FFurnitureState> USaveGameEpopoiia::GetTempleState()
{
	return TArray<FFurnitureState>();
}

void USaveGameEpopoiia::SetTempleState(TArray<FFurnitureState> _templeState)
{
	templeState = _templeState;
}

TArray<int> USaveGameEpopoiia::GetPlayerInventory()
{
	return playerInventory;
}

void USaveGameEpopoiia::SetPlayerInventory(TArray<int> _playerInventory)
{
	playerInventory = _playerInventory;
}

int USaveGameEpopoiia::GetSeed()
{
	return seed;
}

void USaveGameEpopoiia::SetSeed(int _seed)
{
	seed = _seed;
}

TArray<FShopState> USaveGameEpopoiia::GetShopState()
{
	return shopState;
}

void USaveGameEpopoiia::SetShopState(TArray<FShopState> _shopState)
{
	shopState = _shopState;
}

TArray<FNPCsQuest> USaveGameEpopoiia::GetQuests()
{
	return questsOfDay;
}

void USaveGameEpopoiia::SetQuests(TArray<FNPCsQuest> _quests)
{
	questsOfDay = _quests;
}


