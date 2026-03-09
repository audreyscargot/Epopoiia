// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldInteractComponent.h"

#include <gsl/pointers>

#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UHoldInteractComponent::UHoldInteractComponent()
{
	
}

// Called when the game starts
void UHoldInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<AInteractableObject>(GetOwner());
	
}


void UHoldInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHoldInteractComponent::ActivateHold(bool _isActive, APlayerCharacter* _player)
{
	isActiveHold = _isActive;
	if (isActiveHold)
	{
		Owner->RemoveInteractFeedback_Implementation();
		//TODO: Remove Can Be Interacted while held !!
		
		Player = _player;
		Player->OnMovedDelegate.BindDynamic(this, &ThisClass::PushPull);
		Player->OnShouldTurn.BindDynamic(this, &UHoldInteractComponent::Turn);
		
		//Make close Point
		FVector _closestPoint;
		_closestPoint.X = GetPointCloserTo().X;
		_closestPoint.Y = GetPointCloserTo().Y;
		_closestPoint.Z = Player->GetActorLocation().Z;
		
		Player->SetActorLocation(_closestPoint); // Move Player to the closest side 
		FRotator _lookAtRotation = UKismetMathLibrary::FindLookAtRotation(Player->GetActorLocation(), Owner->GetActorLocation());
		Player->SetActorRotation((FRotator (0, _lookAtRotation.Yaw, 0)));
		UE_LOG(LogTemp, Warning, TEXT("%f"), _lookAtRotation.Yaw);
		vectorToPlayer = Owner->GetActorLocation() - Player->GetActorLocation();
	}
	else
	{
		Owner->SetActorLocation(FVector(Player->GetActorLocation().X+vectorToPlayer.X, Player->GetActorLocation().Y+vectorToPlayer.Y, Owner->GetActorLocation().Z));
		Player->OnMovedDelegate.Unbind();
		Player->OnShouldTurn.Unbind();
		Player = nullptr;
	}
}

//Determine which point to move Player
FVector UHoldInteractComponent::GetPointCloserTo()
{
	FVector _closestPoint = Owner->GetActorLocation() + Owner->InteractPoints[0];
	if (Player)
	{
		for (int i = 1; i<4; i++)
		{
			float distance = UKismetMathLibrary::Vector_Distance(Player->GetActorLocation(), Owner->GetActorLocation() + Owner->InteractPoints[i]);
			if (distance < UKismetMathLibrary::Vector_Distance(Player->GetActorLocation(), _closestPoint))
			{
				_closestPoint = Owner->GetActorLocation()+ Owner->InteractPoints[i];
			}
		}
	}
	return _closestPoint;
}

//Push Pull function
void UHoldInteractComponent::PushPull(FVector _direction)
{
		FVector _displacement = Player->GetActorLocation() + vectorToPlayer;
		Owner->SetActorLocation(FVector(_displacement.X, _displacement.Y, Owner->GetActorLocation().Z));
}

void UHoldInteractComponent::AddTurn()
{
	Owner->AddActorWorldRotation(FRotator (0,TurnDirection.Y + TurnDirection.X >= 0 ? -1 : 1,0));
	RotationTemp ++;
	if (RotationTemp > 89)
	{
		GetWorld()->GetTimerManager().ClearTimer(TurnTimerHandle);
		RotationTemp = 0;
		UE_LOG(LogTemp, Warning, TEXT("RotationTemp = 0"));
	}
	
}

void UHoldInteractComponent::Turn(FVector _direction)
{
	TurnDirection = _direction - Owner->GetActorLocation();
	TurnTimerHandle = UKismetSystemLibrary::K2_SetTimer(this, "AddTurn", (0.5/90), true, false, 0, 0);
	UE_LOG(LogTemp, Warning, TEXT("%d"), TurnTimerHandle.IsValid());
}


