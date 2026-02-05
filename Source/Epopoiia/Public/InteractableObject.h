// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

class APlayerCharacter;
class UWidgetComponent;

UCLASS()
class EPOPOIIA_API AInteractableObject : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UWidgetComponent* InteractWidget;
	
private:
	// TO DO : Delete
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess))
	bool bIsOpen = true;
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation(APlayerCharacter* InstigatorPawn) override;
	virtual void CanBeInteracted_Implementation() override;
	virtual void RemoveInteractFeedback_Implementation() override;
	

};
