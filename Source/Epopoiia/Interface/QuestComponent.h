// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Epopoiia/Objects/InteractableNPC.h"
#include "QuestComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EPOPOIIA_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UQuestComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UGameInstanceMain* gameInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AInteractableNPC* owner;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ownerID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FNPCsQuest NPCquest;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int questDialogueIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* availableQuests;
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void CheckQuestSaved();
	
	UFUNCTION(BlueprintCallable)
	virtual void LoadQuests(FNPCsQuest _quest);
	
	UFUNCTION(BlueprintCallable)
	virtual void CreateQuests();
	
	UFUNCTION(BlueprintCallable)
	virtual void MakeDialogues(int _questIndex);
	
	UFUNCTION(BlueprintCallable)
	virtual void SetQuests();
	
	UFUNCTION(BlueprintCallable)
	virtual void FinishQuest(bool _isGoodAnswer);
};
