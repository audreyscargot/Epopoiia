// Fill out your copyright notice in the Description page of Project Settings.


#include "Epopoiia/Interface/InventoryComponent.h"

#include "Blueprint/UserWidget.h"
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
	
}

void UInventoryComponent::AddToInventory(int itemID)
{
	Inventory.Add(itemID);
}

//to use if destroyed or used
void UInventoryComponent::RemoveFromInventory(int itemID)
{
	Inventory.Remove(itemID);
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

void UInventoryComponent::UseItem(int itemID)
{
	OnUseItem.ExecuteIfBound(itemID);
}



