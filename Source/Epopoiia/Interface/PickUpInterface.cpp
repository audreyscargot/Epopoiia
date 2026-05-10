
#include "Epopoiia/Interface/PickUpInterface.h"
#include "InventoryComponent.h"
#include "Epopoiia/Objects/InteractableObject.h"
#include "Epopoiia/Player/PlayerCharacter.h"

UPickUpInterface::UPickUpInterface()
{
}

void UPickUpInterface::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<AInteractableObject>(GetOwner());
	Temp = Cast<AEpopoiiaGameMode>(GetWorld()->GetAuthGameMode())->GetAvailableItems();
	
	//Initialize objet with data from ID row
	FName _row = FName(FString::FromInt(Owner->ID));
	FString _context = "";
	if (Temp && Owner->ID != 0)
	{
		FItemStruct* Row = Temp->FindRow<FItemStruct>(_row, _context , true);
		if (Row)
		{
			ItemProperties = *Row;
			if (ItemProperties.Mesh) Owner->SetMesh(ItemProperties.Mesh); //SetUp Mesh
		}
	}
}

void UPickUpInterface::PickedUp(APlayerCharacter* Player)
{
	if (Player->Inventory->CheckHasSpace())
	{
		Player->Inventory->AddToInventory(ItemProperties.ID);
		Owner->Destroy(true);
	}
}


