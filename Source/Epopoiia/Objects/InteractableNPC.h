// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Epopoiia/Widgets/DetectUserWidget.h"
#include "InteractableObject.h"
#include "Epopoiia/Core/GameInstanceMain.h"
#include "InteractableNPC.generated.h"

USTRUCT(BlueprintType)
struct FGreetings 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Greetings;
};

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Properties")
	int questDailyQuantity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category= "Properties")
	int npcID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Quest")
	FNPCsQuest Quests;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Quest")
	FName activeQuest;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "GameMode")
	UGameInstanceMain* GameInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "GameMode")
	UDataTable* availableQuests;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Dialogue")
	FGreetings greetings;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Dialogue")
	TArray<int> dialogueIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Dialogue")
	int currentQuestIndex;
	
public:
	AInteractableNPC();
	
	void Interact_Implementation(APlayerCharacter* InstigatorPawn) override;
	
	void BeginPlay() override;
	
	UFUNCTION()
	void MakeQuests();
	
	UFUNCTION()
	void AssignQuests();
	
	UFUNCTION()
	void SetActiveQuest();
	
	UFUNCTION(BlueprintCallable)
	void FinishQuest(bool _isGoodAnswer);
	
	UFUNCTION(BlueprintCallable)
	void Thinking();
	
	UFUNCTION(BlueprintCallable)
	void SetDialogueView(APlayerCharacter* InstigatorPawn);
	
	UFUNCTION(BlueprintCallable)
	void AssignDialogueIndex();
};
