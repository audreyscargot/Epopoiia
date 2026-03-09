// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "MovableObject.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInteractInterface;
struct FInputActionValue;

UENUM(BlueprintType)
enum class ELookMoveMode : uint8
{
	FreeMovement = 0 UMETA(DisplayName = "FreeMovement"),
	GridMovement = 1 UMETA(DisplayName = "GridMovement"),
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMoved, FVector, _direction);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnShouldTurn, FVector, _direction);

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractHoldAction;
	
	
	
	


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
	
	//Base Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Trace")
	float TraceLength = 200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Interact")
	AActor* InteractActor;
	
	//Camera & PhoneCamera Parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Properties")
	FTransform CameraRegularTransform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Properties")
	float RegularTargetArmLength = 300.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Phone")
	FTransform CameraPhoneTransform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Phone")
	float PhoneTargetArmLength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Phone")
	bool bUsingPhone = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Phone")
	bool bCanLookMove = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Phone")
	UDetectUserWidget* PhoneWidget;
	
	//Grid Movement Mode
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Grid")
	float cellSize = 100.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Grid")
	bool canGridMove = true;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Enum", meta = (AllowPrivateAccess = "true"))
	ELookMoveMode LookMoveMode;
	
	int GetTimeRewindAbilityLevel();
	FTransform GetCameraRegularTransform();
	float GetRegularTargetArmLength();
	void SetCanLookMove(bool _canLookMove);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoGridMove(float Right, float Forward);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SmoothGridMove(FVector _basePosition, FVector _displacement, float _movementSpeed);
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void ResetCanGridMove();
	
	UFUNCTION(BlueprintCallable)
	virtual void CallDelegate(FVector _displacement, bool _shouldTurn);
	
	//Delegate OnMoved for moving objects
	UPROPERTY(BlueprintReadWrite, Category= "Delegate")
	FOnMoved OnMovedDelegate;
	
	//Delegate for turning objects
	UPROPERTY(BlueprintReadWrite, Category= "Delegate")
	FOnShouldTurn OnShouldTurn;
	
	/**Interaction Linetrace**/
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void Interact();
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void InteractHold();
	
	/** Look for Interaction **/
	UFUNCTION(BlueprintCallable)
	virtual void LookForInteract();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCameraView(bool bIsPhoneView, FTransform CameraTransform, float ArmLength);
	
	/** Open Phone Function **/
	UFUNCTION(BlueprintCallable)
	void OpenPhone();

	UFUNCTION(BlueprintCallable)
	void CreatePhoneWidget(TSubclassOf<class UDetectUserWidget> _widgetClass);
};
