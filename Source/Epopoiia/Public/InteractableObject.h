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
	
	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UWidgetComponent* InteractWidget;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsInteractable = true;
	
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
	
	UFUNCTION(BlueprintCallable)
	void FeedbackWidgetAppear();
	

};
