// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSwitcherBox.generated.h"

class UBoxComponent;
UCLASS()
class EPOPOIIA_API ALevelSwitcherBox : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> CollisionBox;
	
public:	
	// Sets default values for this actor's properties
	ALevelSwitcherBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSoftObjectPtr<UWorld> LevelToOpen;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherOverlappedComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION(BlueprintCallable)
	virtual void SwitchWorld();

};
