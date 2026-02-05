// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInteractInterface;
struct FInputActionValue;

UCLASS()
class EPOPOIIA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input", meta = (AllowPrivateAccess))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enhanced Input", meta = (AllowPrivateAccess))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Enhanced Input", meta = (AllowPrivateAccess))
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Enhanced Input", meta = (AllowPrivateAccess))
	UInputAction* OpenPhoneAction;
	
	//Front Camera (for phone use)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess))
	UCameraComponent* FrontViewCamera;


protected:
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	// Ability level variable, TODO : change if multiple abilities
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Properties", meta = (AllowPrivateAccess = "true"))
	int TimeRewindAbilityLevel = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Trace")
	float TraceLength = 200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Interact")
	AActor* InteractActor;

public:
	
	int GetTimeRewindAbilityLevel();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw);
	
	/**Interaction Linetrace**/
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void Interact();
	
	/** Look for Interaction **/
	UFUNCTION(BlueprintCallable)
	virtual void LookForInteract();
	
	/** Open Phone Function **/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OpenPhone();

};
