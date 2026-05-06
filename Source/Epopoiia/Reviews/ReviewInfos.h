#pragma once

#include "CoreMinimal.h"
#include "ReviewInfos.generated.h"

USTRUCT(BlueprintType)
struct FReviewBaseStruct : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int starRating = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> spiritReview;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> templeReview;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> generalReview;
};