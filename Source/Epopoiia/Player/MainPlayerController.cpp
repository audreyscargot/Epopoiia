// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent(); //Appelle le code de la classe parent
	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	
}
