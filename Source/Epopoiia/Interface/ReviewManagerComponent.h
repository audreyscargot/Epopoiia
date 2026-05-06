// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ReviewManagerComponent.generated.h"

class UGameInstanceMain;

USTRUCT(BlueprintType)
struct FReviewStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString reviewNPCName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int reviewGrade;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString reviewText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* pfpTexture;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EPOPOIIA_API UReviewManagerComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite)
	UGameInstanceMain* gameInstance;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FReviewStruct> reviews;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UDataTable* reviewDataTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> reviewersName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UTexture2D*> reviewTexture;

public:
	// Sets default values for this component's properties
	UReviewManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	int GetTempleReview();
	
	UFUNCTION(BlueprintCallable)
	int GetQuestReview();
	
	UFUNCTION(BlueprintCallable)
	void MakeGeneralReviewGrade();
	
	UFUNCTION(BlueprintCallable)
	FString GetRandomLine(int _index, int _type);
	
	UFUNCTION(BlueprintCallable)
	void MakeReview(bool _isQuestSucceeded);
	
	UFUNCTION(BlueprintCallable)
	void AddReview(FString _reviewNPCName, int _reviewGrade, FString _reviewText, UObject* _pfpTexture);
	
};
