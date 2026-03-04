// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DetectUserWidget.h"
#include "InteractableObject.h"
#include "InteractableNPC.generated.h"

/**
 * 
 */
UCLASS()
class EPOPOIIA_API AInteractableNPC : public AInteractableObject
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* SkeletalMesh;

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Interact")
	FTransform cameraInteractTransform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Interact")
	float interactTargetArmLength = 150.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Interact")
	bool isInteracted = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Widget")
	TSubclassOf<UDetectUserWidget> interactWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Interact")
	TObjectPtr<UUserWidget> interactWidgetRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Properties")
	FRotator regularRotator;
	
public:
	AInteractableNPC();
	
	void Interact_Implementation(APlayerCharacter* InstigatorPawn) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Dialogue();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Thinking();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetDialogueView(APlayerCharacter* InstigatorPawn);
};
