// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "FixableObject.generated.h"

class UStaticMeshComponent;

UCLASS()
class EPOPOIIA_API AFixableObject : public AInteractableObject
{
	GENERATED_BODY()
	
	UPROPERTY(Category=Actor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;
	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = true, InstanceEditable = true))
	int RequiredLevel;
	
	//Mesh to change (broken and repaired vesrion)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = true))
	UStaticMesh* BrokenMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = true))
	UStaticMesh* RepairedMesh;
	
public:
	AFixableObject();
	
	virtual void Interact_Implementation(APlayerCharacter* InstigatorPawn) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Repair();
	
};
