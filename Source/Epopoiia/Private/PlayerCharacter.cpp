// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InteractInterface.h"
#include "Epopoiia/Epopoiia.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	
	FrontViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FrontViewCamera"));
	FrontViewCamera->SetupAttachment(CameraBoom);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
		EnhancedInputComponent->BindAction(OpenPhoneAction, ETriggerEvent::Started, this, &APlayerCharacter::OpenPhone);
	};
	
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoLook(LookAxisVector.X);
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
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
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
		UE_LOG(LogTemp, Warning, TEXT("Rotation: %f - %f - %f"), ForwardDirection.X, ForwardDirection.Y, ForwardDirection.Z);
		
	}
}

void APlayerCharacter::Interact()
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
			IInteractInterface::Execute_Interact(HitActor, this);
			UE_LOG(LogTemp, Warning, TEXT("Interacted with: %s"), *HitActor->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit actor doesn't implement interaction interface"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No hit"));
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
			if (HitActor != InteractActor && InteractActor != nullptr) IInteractInterface::Execute_RemoveInteractFeedback(InteractActor);
			InteractActor = HitActor;
			IInteractInterface::Execute_CanBeInteracted(HitActor);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActor->GetName());
		}
	}
	else
	{
		if (InteractActor != nullptr)
		{
			IInteractInterface::Execute_RemoveInteractFeedback(InteractActor);
			UE_LOG(LogTemp, Warning, TEXT("RemoveFeedback"));
		}
		else UE_LOG(LogTemp, Warning, TEXT("NoActorRegistered"));
	}
}

void APlayerCharacter::OpenPhone_Implementation()
{
	
	
	
}


// Getter
int APlayerCharacter::GetTimeRewindAbilityLevel()
{
	return TimeRewindAbilityLevel;
}
