// Fill out your copyright notice in the Description page of Project Settings.


#include "ReviewManagerComponent.h"

#include "Epopoiia/Core/GameInstanceMain.h"
#include "Epopoiia/Reviews/ReviewInfos.h"

const int middleGradeFurniture = 1;
const int highestGradeFurniture = 2;

// Sets default values for this component's properties
UReviewManagerComponent::UReviewManagerComponent()
{
	
}



void UReviewManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	gameInstance = Cast<UGameInstanceMain>(GetWorld()->GetGameInstance());
	if (gameInstance)
	{
		reviews = gameInstance->GetReviews();
	}
}

int UReviewManagerComponent::GetTempleReview()
{
	int _furnitureTotal = gameInstance->GetTempleState().Num();
	for (auto fixed : gameInstance->GetTempleFixedState())
	{
		if (fixed.Value == true)
		{
			_furnitureTotal += 1;
		}
	}
	if (_furnitureTotal >= highestGradeFurniture)
	{
		return 3;
	}
	if (_furnitureTotal >= middleGradeFurniture)
	{
		return 2;
	}
	return 1;
}

int UReviewManagerComponent::GetQuestReview()
{
	return 0;
}

void UReviewManagerComponent::MakeGeneralReviewGrade()
{
	
	if (gameInstance)
	{
		int _generalGrade = GetTempleReview() + GetQuestReview();
		gameInstance->SetReviewGrade(_generalGrade);
	}
}

FString UReviewManagerComponent::GetRandomLine(int _index, int _type)
{
	TArray<FName> _dataRow = reviewDataTable->GetRowNames();
	if (_dataRow.IsValidIndex(_index))
	{
		FReviewBaseStruct* _row = reviewDataTable->FindRow<FReviewBaseStruct>(_dataRow[_index], "", true);
		if (_row)
		{
			TArray<FString> _column = _type == 0 ? _row->templeReview : _row->spiritReview;
			_column = _type == 2 ? _row->generalReview : _column;
			int _randomLine = FMath::RandRange(0, _column.Num() - 1 );
			if (_column.IsValidIndex(_randomLine))
			{
				FString _reviewText = _column[_randomLine];
				
				return _reviewText;
			}
		}
	}
	return "";
}

void UReviewManagerComponent::MakeReview(bool _isQuestSucceeded)
{
	if (reviewDataTable)
	{
		
		FString _templeReview = "";
		
		int _random = _isQuestSucceeded ? 3 : 1;
		int _indexReview = FMath::RandRange(_random-1, _random+1);
		_templeReview.Append(GetRandomLine(_indexReview, 1));
		_templeReview.Append(" ");
		
		int _indexTemple = GetTempleReview();
		_templeReview.Append(GetRandomLine(_indexTemple, 0));
		_templeReview.Append(" ");
		
		int _indexGeneral = gameInstance->GetReviewGrade();
		_templeReview.Append(GetRandomLine(_indexGeneral, 2));
		
		FString _randomName = "@" + reviewersName[FMath::RandRange(0,reviewersName.Num()-1)];
		
		int _randomGrade = GetTempleReview() - FMath::RandRange(0, GetTempleReview() - 1);
		_randomGrade += _isQuestSucceeded ? 1 : 0;
		
		int _randomPfpIndex = FMath::RandRange(0, reviewTexture.Num() - 1);
		
		AddReview(_randomName, _randomGrade, _templeReview, _randomPfpIndex);
		MakeGeneralReviewGrade();
	}
}

void UReviewManagerComponent::AddReview(FString _reviewNPCName, int _reviewGrade, FString _reviewText, int _reviewPfpIndex)
{
	reviews.Add(FReviewStruct(_reviewNPCName, _reviewGrade, _reviewText, _reviewPfpIndex));
	gameInstance->SetReviews(reviews);
}


