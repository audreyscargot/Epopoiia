// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.generated.h"

class AInteractableObject;

UENUM(BlueprintType)
enum class ESpirit : uint8
{
	None = 0,
	Korrigan = 1 UMETA(DisplayName = "Korrigan"),
	Willowisp = 2 UMETA(DisplayName = "Will'o the Wisp"),
};

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;
};

USTRUCT(BlueprintType)
struct FQuestsInfo : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESpirit Spirit = ESpirit::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> DialogueSentences;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ThinkingBubbles;
};