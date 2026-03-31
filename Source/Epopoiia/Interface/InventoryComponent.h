
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Epopoiia/Core/EpopoiiaGameMode.h"
#include "InventoryComponent.generated.h"

class UBaseWidget;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnUseItem, int, itemID);

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
	TArray<int> Inventory;
	
	UPROPERTY()
	FOnUseItem OnUseItem;
	
	UPROPERTY()
	int inventorySlots = 10;
	
	UPROPERTY()
	AEpopoiiaGameMode* gameMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedPrivateAccess = true))
	UBaseWidget* InventoryWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedPrivateAccess = true))
	TSubclassOf<UBaseWidget> InventoryWidgetClass;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* ItemsData;
	
	UFUNCTION()
	virtual void AddToInventory(int itemID);
	
	UFUNCTION()
	virtual void RemoveFromInventory(int itemID);
	
	UFUNCTION()
	virtual bool CheckHasSpace();
	
	UFUNCTION()
	virtual void OpenInventory();
	
	// Use Object Functions
	UFUNCTION(BlueprintCallable)
	virtual void UseItem(int itemID);

		
};
