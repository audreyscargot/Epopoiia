// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableShop.h"

#include "Epopoiia/Core/EpopoiiaGameMode.h"
#include "Epopoiia/Core/GameInstanceMain.h"
#include "Kismet/KismetArrayLibrary.h"


// Sets default values
AInteractableShop::AInteractableShop()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractableShop::BeginPlay()
{
	Super::BeginPlay();
	gameInstance = Cast<UGameInstanceMain>(GetGameInstance());
	Cast<AEpopoiiaGameMode>(GetWorld()->GetAuthGameMode())->OnSeedUpdated.AddDynamic(this, &AInteractableShop::CheckIsShopSaved);
}

void AInteractableShop::Interact_Implementation(APlayerCharacter* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
}

TArray<FShopState> AInteractableShop::GetShopInventory()
{
	return shopInventory;
}

void AInteractableShop::CheckIsShopSaved()
{
	if (!gameInstance->GetShopState().IsEmpty())
	{
		LoadShop();
		return;
	}
	MakeShop();
}

void AInteractableShop::MakeShop()
{
	if (dtAvailableItems)
	{
		TArray<FName> _availableItems = dtAvailableItems->GetRowNames();
		for (int i = 0; i < shopSlotNumber; i++)
		{
			int _index = FMath::RandRange(0, _availableItems.Num() - 1);
			if (_availableItems.IsValidIndex(_index))
			{
				FShopState _newItem = FShopState(_availableItems[_index], false);
				shopInventory.Add(_newItem);
				_availableItems.RemoveAt(_index, EAllowShrinking::Yes);
			}
		}
		gameInstance->SetShopState(shopInventory);
		gameInstance->SaveShopState();
		gameInstance->SaveGameToSlot();
	}
}

void AInteractableShop::LoadShop()
{
	shopInventory = gameInstance->GetShopState();
}

void AInteractableShop::UpdateShop(FName _objectID, bool _hasBeenBought, int _slot)
{
	shopInventory[_slot] = FShopState(_objectID, _hasBeenBought);
	gameInstance->SetShopState(shopInventory);
}


