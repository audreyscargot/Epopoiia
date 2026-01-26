// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Epopoiia/Epopoiia.h"

AMyPlayerController::AMyPlayerController()
{
	
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : InputMapping)
			{
				Subsystem->AddMappingContext(CurrentContext,0);
			}
		}
	}
}
