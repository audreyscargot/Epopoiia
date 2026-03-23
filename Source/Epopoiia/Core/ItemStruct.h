// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.generated.h"

class AInteractableObject;

USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AInteractableObject> actorClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;
};