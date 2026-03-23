// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DetectUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class EPOPOIIA_API UDetectUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void MakeDetectionAppear();
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void RemoveWidget();
	
};
