// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include <ranges>

#include "DetectUserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HoldInteractComponent.h"
#include "InputActionValue.h"
#include "InteractInterface.h"
#include "Blueprint/UserWidget.h"
#include "Epopoiia/Epopoiia.h"
#include "Kismet/KismetMathLibrary.h"

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

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetController()->SetControlRotation(FRotator (0,0,0));
	
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
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		EnhancedInputComponent->BindAction(InteractHoldAction, ETriggerEvent::Triggered, this, &APlayerCharacter::InteractHold);
		EnhancedInputComponent->BindAction(OpenPhoneAction, ETriggerEvent::Started, this, &APlayerCharacter::OpenPhone);
	};
	
}

// NOT USED : TO REMOVE
void APlayerCharacter::Look(const FInputActionValue& Value)
{
	
	// if (bCanLookMove)
	// {
	// 	switch (LookMoveMode)
	// 	{
	// 	case ELookMoveMode::FreeMovement :
	// 		FVector2D LookAxisVector = Value.Get<FVector2D>();
	// 		DoLook(LookAxisVector.X);
	// 		break;
	// 	case ELookMoveMode::GridMovement :
	// 		break;
	// 	}
	// 	
	// }
}

void APlayerCharacter::DoLook(float Yaw)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
	}
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
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
		
	}
}

void APlayerCharacter::DoGridMove(float Right, float Forward)
{
	FVector _moveVector = (Forward != 0) ? GetActorForwardVector() : GetActorRightVector();
	float _moveSign = (Forward != 0) ? Forward : Right;
	FVector _displacement = GetActorLocation() + _moveVector * cellSize * UKismetMathLibrary::SignOfFloat(_moveSign);
	SetActorLocation(_displacement);
	if (_moveVector.Length() > 0)
	{
		OnMovedDelegate.ExecuteIfBound(_displacement);
	}
	UE_LOG(LogTemp, Warning, TEXT("%f"), _moveVector.Length());
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
	UE_LOG(LogTemp, Warning, TEXT("Hold Started"));
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

void APlayerCharacter::LookForInteract()
{
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + (GetActorForwardVector() * TraceLength);
	
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, bHit ? FColor::Green : FColor::Red, false, 1.0f, 0, 1.0f);
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

// Camera feedback movement for phone
void APlayerCharacter::SetCameraView_Implementation(bool bIsPhoneView, FTransform CameraTransform, float ArmLength)
{
	bUsingPhone = bIsPhoneView;
	bCanLookMove = !bUsingPhone;
	
}

//Phone
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

// Getter
int APlayerCharacter::GetTimeRewindAbilityLevel()
{
	return TimeRewindAbilityLevel;
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
