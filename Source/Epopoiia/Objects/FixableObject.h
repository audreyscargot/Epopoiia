// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Epopoiia/Core/ItemStruct.h"
#include "FixableObject.generated.h"

class UStaticMeshComponent;

UCLASS()
class EPOPOIIA_API AFixableObject : public AInteractableObject
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = true))
	UWidgetComponent* RepairedWidget;
	
	
	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = true, InstanceEditable = true))
	int RequiredLevel;
	
	//Mesh to change (broken and repaired vesrion)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = true))
	UStaticMesh* BrokenMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = true))
	UStaticMesh* RepairedMesh;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = true))
	bool isFixed = false;
	
	AFixableObject();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact_Implementation(APlayerCharacter* InstigatorPawn) override;
	virtual void CanBeInteracted_Implementation() override;
	virtual void RemoveInteractFeedback_Implementation() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Repair();
	
	virtual void MakeMesh() override;
	
	UFUNCTION(BlueprintNativeEvent)
	void MakeFeedback();
};
