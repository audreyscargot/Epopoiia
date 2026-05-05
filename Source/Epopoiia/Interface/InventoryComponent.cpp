// Fill out your copyright notice in the Description page of Project Settings.


#include "Epopoiia/Interface/InventoryComponent.h"

#include "Blueprint/UserWidget.h"
#include "Epopoiia/Core/GameInstanceMain.h"
#include "Epopoiia/Widgets/BaseWidget.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	gameMode = Cast<AEpopoiiaGameMode>(GetWorld()->GetAuthGameMode());
	OnUseItem.BindDynamic(gameMode, &AEpopoiiaGameMode::UseObject);
	gameMode->OnSuccessfullyUsed.AddDynamic(this, &UInventoryComponent::RemoveFromInventory);
	
	UGameInstanceMain* _gameInstance = Cast<UGameInstanceMain>(GetWorld()->GetGameInstance());
	if (_gameInstance)
	{
		OnInventoryUpdated.AddDynamic(_gameInstance, &UGameInstanceMain::UpdateGIInventory);
	}
	
}

void UInventoryComponent::AddToInventory(int itemID)
{
	Inventory.Add(itemID);
	OnInventoryUpdated.Broadcast(this);
}

//to use if destroyed or used
void UInventoryComponent::RemoveFromInventory(int itemID)
{
	Inventory.RemoveSingle(itemID);
	OnInventoryUpdated.Broadcast(this);
}

bool UInventoryComponent::CheckHasSpace()
{
	if (Inventory.Num() >= inventorySlots)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory is %d"), Inventory.Num());
		return false;
	}
	return true;
}

void UInventoryComponent::OpenInventory()
{
	InventoryWidget = Cast<UBaseWidget>(CreateWidget(GetWorld(), InventoryWidgetClass, "Inventory"));
	InventoryWidget->AddToViewport();
}

TArray<int> UInventoryComponent::GetInventory()
{
	return Inventory;
}

void UInventoryComponent::SetInventory(TArray<int> _inventory)
{
	Inventory = _inventory;
}

void UInventoryComponent::UseItem(int itemID)
{
	OnUseItem.ExecuteIfBound(itemID);
	OnInventoryUpdated.Broadcast(this);
}



