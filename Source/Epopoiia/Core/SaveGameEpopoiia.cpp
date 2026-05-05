// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameEpopoiia.h"

TArray<FFurnitureState> USaveGameEpopoiia::GetTempleState()
{
	return templeState;
}

void USaveGameEpopoiia::SetTempleState(TArray<FFurnitureState> _templeState)
{
	templeState = _templeState;
}

TMap<int, bool> USaveGameEpopoiia::GetFixedState()
{
	return templeFixedState;
}

void USaveGameEpopoiia::SetFixedState(TMap<int, bool> _fixedState)
{
	templeFixedState = _fixedState;
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

bool USaveGameEpopoiia::GetHasAltarBeenUsed()
{
	return hasAltarBeenUsed;
}

void USaveGameEpopoiia::SetHasAltarBeenUsed(bool _hasAltarBeenUsed)
{
	hasAltarBeenUsed = _hasAltarBeenUsed;
}

int USaveGameEpopoiia::GetTempleReviewGrade()
{
	return templeReviewGrade;
}

void USaveGameEpopoiia::SetTempleReviewGrade(int _templeReviewGrade)
{
	templeReviewGrade = _templeReviewGrade;
}

TArray<FReviewStruct> USaveGameEpopoiia::GetReviews()
{
	return reviews;
}

void USaveGameEpopoiia::SetReviews(TArray<FReviewStruct> _reviews)
{
	reviews = _reviews;
}

int USaveGameEpopoiia::GetPlayerMoney()
{
	return playerMoney;
}

void USaveGameEpopoiia::SetPlayerMoney(int _playerMoney)
{
	playerMoney = _playerMoney;
}

int USaveGameEpopoiia::GetPlayerTimeRewindAbility()
{
	return playerTimeRewindAbilityLevel;
}

void USaveGameEpopoiia::SetPlayerTimeRewindAbility(int _playerTimeRewindAbility)
{
	playerTimeRewindAbilityLevel = _playerTimeRewindAbility;
}


