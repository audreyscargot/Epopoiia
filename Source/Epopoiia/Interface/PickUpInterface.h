// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Epopoiia/Core/ItemStruct.h"
#include "PickUpInterface.generated.h"


class APlayerCharacter;
struct FItemStruct;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EPOPOIIA_API UPickUpInterface : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickUpInterface();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* Temp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FItemStruct ItemProperties;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	AInteractableObject* Owner;
	
virtual void BeginPlay() override;
	
public:	
	
	UFUNCTION()
	virtual void PickedUp(APlayerCharacter* Player);

		
};
