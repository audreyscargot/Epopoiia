
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Epopoiia/Core/EpopoiiaGameMode.h"
#include "InventoryComponent.generated.h"

class UBaseWidget;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnUseItem, int, itemID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, UInventoryComponent*, inventory);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EPOPOIIA_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedPrivateAccess = true))
	TArray<int> Inventory = {1,2,1};
	
	UPROPERTY()
	FOnUseItem OnUseItem;
	
	UPROPERTY()
	AEpopoiiaGameMode* gameMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedPrivateAccess = true))
	UBaseWidget* InventoryWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedPrivateAccess = true))
	TSubclassOf<UBaseWidget> InventoryWidgetClass;

public:	
	UPROPERTY()
	int inventorySlots = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* ItemsData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOnInventoryUpdated OnInventoryUpdated;
	
	UFUNCTION()
	virtual void AddToInventory(int itemID);
	
	UFUNCTION()
	virtual void RemoveFromInventory(int itemID);
	
	UFUNCTION()
	virtual bool CheckHasSpace();
	
	UFUNCTION()
	virtual void OpenInventory();
	
	UFUNCTION()
	TArray<int> GetInventory();
	
	UFUNCTION()
	void SetInventory(TArray<int> _inventory);
	
	// Use Object Functions
	UFUNCTION(BlueprintCallable)
	virtual void UseItem(int itemID);

		
};
