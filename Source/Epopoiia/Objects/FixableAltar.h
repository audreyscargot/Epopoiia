// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FixableObject.h"
#include "FixableAltar.generated.h"

class UGameInstanceMain;

UCLASS()
class EPOPOIIA_API AFixableAltar : public AFixableObject
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* OfferingMesh;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameInstanceMain* gameInstance; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Properties")
	int currentMoney = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Properties")
	bool hasBeenUsed = false;
	
public:
	// Sets default values for this actor's properties
	AFixableAltar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Interact_Implementation(APlayerCharacter* InstigatorPawn) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void MakeMoney();
	
	UFUNCTION(BlueprintCallable)
	virtual void SetOfferingVisibility(bool _shouldBeVisible);
	
	UFUNCTION()
	virtual void SetOfferingLocation();
	
	void Repair() override;

};
