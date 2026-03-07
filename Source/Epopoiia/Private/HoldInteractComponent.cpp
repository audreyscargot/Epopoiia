// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldInteractComponent.h"

#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UHoldInteractComponent::UHoldInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHoldInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<AInteractableObject>(GetOwner());
	
}


// Called every frame
void UHoldInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHoldInteractComponent::ActivateHold(bool _isActive, APlayerCharacter* _player)
{
	isActiveHold = _isActive;
	if (isActiveHold)
	{
		Player = _player;
		Player->OnMovedDelegate.BindDynamic(this, &ThisClass::PushPull);
		
		//Make closest Point
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
		Player->OnMovedDelegate.Unbind();
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

//Push Pull functions
void UHoldInteractComponent::PushPull(FVector _direction)
{
	UE_LOG(LogTemp, Warning, TEXT("%f"), _direction.X);
	FVector _displacement = vectorToPlayer + _direction;
	Owner->SetActorLocation(FVector(_displacement.X, _displacement.Y, Owner->GetActorLocation().Z));
}


