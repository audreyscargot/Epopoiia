// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

class UBoxComponent;
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
	
	UPROPERTY(Category=Actor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsInteractable = true;
	
	
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> InteractPoints = {GetActorLocation(), GetActorLocation(), GetActorLocation(), GetActorLocation()} ;
	
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UFUNCTION(BlueprintCallable)
	FVector MakeInteractPoints(FVector _direction);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation(APlayerCharacter* InstigatorPawn) override;
	virtual void CanBeInteracted_Implementation() override;
	virtual void RemoveInteractFeedback_Implementation() override;
	
	UFUNCTION(BlueprintCallable)
	void FeedbackWidgetAppear();
	

};
