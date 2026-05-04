// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include <ranges>

#include "Epopoiia/Widgets/DetectUserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Epopoiia/Interface/HoldInteractComponent.h"
#include "InputActionValue.h"
#include "Epopoiia/Interface/InteractInterface.h"
#include "Blueprint/UserWidget.h"
#include "Epopoiia/Epopoiia.h"
#include "Epopoiia/Core/GameInstanceMain.h"
#include "Epopoiia/Interface/InventoryComponent.h"
#include "Epopoiia/Interface/PickUpInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	
	CameraRegularTransform = CameraBoom->GetRelativeTransform();

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetController()->SetControlRotation(FRotator (0,0,0));
	GameMode = Cast<AEpopoiiaGameMode>(GetWorld()->GetAuthGameMode());
	gameInstance = Cast<UGameInstanceMain>(GetWorld()->GetGameInstance());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LookForInteract();

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		EnhancedInputComponent->BindAction(InteractHoldAction, ETriggerEvent::Triggered, this, &APlayerCharacter::InteractHold);
		EnhancedInputComponent->BindAction(OpenPhoneAction, ETriggerEvent::Started, this, &APlayerCharacter::OpenPhone);
		EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Triggered,this, &APlayerCharacter::TryPickUp);
	};
	
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (bCanLookMove)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();
		switch (LookMoveMode)
		{
		case ELookMoveMode::FreeMovement:
			DoMove(MovementVector.X, MovementVector.Y);
			break;
		case ELookMoveMode::GridMovement: 
			DoGridMove(MovementVector.X, MovementVector.Y);
			break;
		}
		
		
	}
	
}

void APlayerCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		currentState = PushPullState::DEFAULT;
		
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

//Grid move system when pushing/pulling furniture (depends on cellSize)
void APlayerCharacter::DoGridMove(float Right, float Forward)
{
	if (Right == 0 && Forward == 0) currentState = PushPullState::DEFAULT;
	
	float _timeToMove = 0.5;
	FVector _moveVector = Forward != 0 ? FVector(1,0,0) : FVector(0,1,0);
	float _moveSign = UKismetMathLibrary::SignOfFloat(UKismetMathLibrary::Abs(Forward) > 0.2 ? Forward : Right);
	
	FVector _displacement = GetActorLocation() + _moveVector * cellSize * _moveSign;
	
	if (canGridMove)
	{
		bool _shouldTurn = UKismetMathLibrary::Abs(UKismetMathLibrary::Dot_VectorVector(_moveVector, GetActorForwardVector())) < 0.01;
		if (_shouldTurn)
		{
			currentState = PushPullState::DEFAULT;
			OnShouldTurn.ExecuteIfBound(_moveVector*_moveSign);
		}
		else
		{
			if (_displacement.X > GameMode->GetGridMinX() && _displacement.X < GameMode->GetGridMaxX() && _displacement.Y > GameMode->GetGridMinY() && _displacement.Y < GameMode->GetGridMaxY())
			{
				UE_LOG(LogTemp, Warning, TEXT("Y Grid %d"), GameMode->GetGridMinY());
				UE_LOG(LogTemp, Warning, TEXT("displacement %f"), _displacement.Y);
				SmoothGridMove_Implementation(GetActorLocation(), _displacement, _timeToMove);
				//Animation state function
				if (UKismetMathLibrary::Dot_VectorVector(_moveVector*_moveSign, GetMesh()->GetForwardVector()) < 0) currentState = PushPullState::PULL;
				else currentState = PushPullState::PUSH;
			}
		}
		canGridMove = false;
		UKismetSystemLibrary::K2_SetTimer(this, "ResetCanGridMove", _timeToMove*1.5, false, false);
	}
}

//Blueprint implemented function for movement timeline
void APlayerCharacter::SmoothGridMove_Implementation(FVector _basePosition, FVector _displacement, float _movementSpeed)
{
	SmoothGridMove(_basePosition, _displacement, _movementSpeed);
}

void APlayerCharacter::ResetCanGridMove()
{
	canGridMove = true;
}

void APlayerCharacter::CallDelegate(FVector _displacement, bool _shouldTurn)
{
	OnMovedDelegate.ExecuteIfBound(_displacement);
}

// Interaction System
void APlayerCharacter::Interact()
{
	if (InteractActor)
	{
		IInteractInterface::Execute_Interact(InteractActor, this);
	}
}

void APlayerCharacter::InteractHold()
{
	LookMoveMode = ELookMoveMode::FreeMovement;
	if (InteractActor)
	{
		UHoldInteractComponent* HoldComponent = InteractActor->GetComponentByClass<UHoldInteractComponent>();
		if (HoldComponent)
		{
			if (HoldComponent->isActiveHold)
			{
				HoldComponent->ActivateHold(false, this);
			}
			else
			{
				HoldComponent->ActivateHold(true, this);
				LookMoveMode = ELookMoveMode::GridMovement;
			}
		}
	}
}

//Tick function, linetrace to check for interactable interface
void APlayerCharacter::LookForInteract()
{
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + (GetActorForwardVector() * TraceLength);
	
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->Implements<UInteractInterface>())
		{
			if (HitActor != InteractActor) 
			{
				if (InteractActor)
				{
					IInteractInterface::Execute_RemoveInteractFeedback(InteractActor);
				}
				InteractActor = HitActor;
				IInteractInterface::Execute_CanBeInteracted(HitActor);
				UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActor->GetName());
			}
			
		}
	}
	else
	{
		if (InteractActor)
		{
			IInteractInterface::Execute_RemoveInteractFeedback(InteractActor);
		}
		InteractActor = nullptr;
	}
}

//Pick Up
void APlayerCharacter::TryPickUp()
{
	if (InteractActor)
	{
		UPickUpInterface* _tempPickUp = InteractActor->GetComponentByClass<UPickUpInterface>();
		if (_tempPickUp)
		{
			_tempPickUp->PickedUp(this);
		}
	}
}

// Camera feedback movement for phone
void APlayerCharacter::SetCameraView_Implementation(bool bIsPhoneView, FTransform CameraTransform, float ArmLength)
{
	bUsingPhone = bIsPhoneView;
	bCanLookMove = !bUsingPhone;
	
}

//Phone system
void APlayerCharacter::OpenPhone()
{
	UE_LOG(LogTemp, Warning, TEXT("Open Phone"));
	FTransform Transform = bUsingPhone? CameraRegularTransform : CameraPhoneTransform;
	float Length = bUsingPhone? RegularTargetArmLength : PhoneTargetArmLength;
	SetCameraView(!bUsingPhone, Transform, Length);
}

void APlayerCharacter::CreatePhoneWidget(TSubclassOf<class UDetectUserWidget> PhoneClass)
{
	if (bUsingPhone)
	{
		PhoneWidget = Cast<UDetectUserWidget>(CreateWidget(GetWorld(), PhoneClass, "PhoneWidget"));
		PhoneWidget->AddToViewport();
		PhoneWidget->MakeDetectionAppear();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *PhoneWidget->GetName());
	}
	else
	{
		if (PhoneWidget)
		{
			PhoneWidget = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Removed"));
		}
	}
}

void APlayerCharacter::UpdateTimeRewindAbility(int _progress)
{
	if (gameInstance)
	{
		gameInstance->SetTimeRewindAbility(_progress);
		gameInstance->SavePlayerTimeRewindAbility();
	}
}

FTransform APlayerCharacter::GetCameraRegularTransform()
{
	return CameraRegularTransform;
}

float APlayerCharacter::GetRegularTargetArmLength()
{
	return RegularTargetArmLength;
}

void APlayerCharacter::SetCanLookMove(bool _canLookMove)
{
	bCanLookMove = _canLookMove;
}
