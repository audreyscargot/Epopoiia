
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
struct FMythipediaPost
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString playerPost;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> botAnswers;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> usedWords;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int date;
};

UENUM(BlueprintType)
enum class EVocabularyType : uint8
{
	None = 0,
	Noun = 1,
	Verb = 2,
	Adjective = 3,
};

UENUM(BlueprintType)
enum class EObjectType : uint8
{
	None = 0,
	Furniture = 1,
	QuestObject = 2,
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
	TSubclassOf<AInteractableObject> actorClass = nullptr ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* FixedMesh = nullptr ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int levelOfFix = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int price = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EObjectType ObjectType = EObjectType::Furniture;
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
	TMap<FString, EVocabularyType> learnedVocabulary;
};