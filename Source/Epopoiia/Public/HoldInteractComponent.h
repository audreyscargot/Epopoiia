// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HoldInteractComponent.generated.h"


class AInteractableObject;
class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EPOPOIIA_API UHoldInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoldInteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	APlayerCharacter* Player;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	AInteractableObject* Owner;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	FVector vectorToPlayer;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	FTimerHandle TurnTimerHandle;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	FVector TurnDirection;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	float RotationTemp;
	
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	bool isActiveHold = false;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION( BlueprintCallable)
	virtual void ActivateHold(bool _isActive, APlayerCharacter* _player);
	
	UFUNCTION( BlueprintCallable)
	FVector GetPointCloserTo();
	
	UFUNCTION(BlueprintCallable)
	virtual void PushPull(FVector _direction);
	
	UFUNCTION()
	virtual void Turn(FVector _direction);
	
	UFUNCTION()
	virtual void AddTurn();
	
};
