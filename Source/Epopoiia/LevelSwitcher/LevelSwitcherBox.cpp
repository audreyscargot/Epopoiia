// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSwitcherBox.h"

#include "Epopoiia/Player/PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Epopoiia/Core/GameInstanceMain.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelSwitcherBox::ALevelSwitcherBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelSwitcherBox::BeginOverlap);
	}

}

// Called when the game starts or when spawned
void ALevelSwitcherBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelSwitcherBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSwitcherBox::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherOverlappedComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor)) StartSwitchWorld();
}

void ALevelSwitcherBox::SwitchWorld()
{
	SendToSave();
	FString Options = "";
	LevelToOpen.LoadSynchronous();
	if (!LevelToOpen.IsNull()) UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),LevelToOpen , true, Options);
	UE_LOG(LogTemp, Warning, TEXT("%d"), LevelToOpen.IsValid());
}

void ALevelSwitcherBox::StartSwitchWorld()
{
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0,1,1,FLinearColor(0,0,0,0), true, true);
	UGameplayStatics::GetPlayerPawn(GetWorld(),0)->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UKismetSystemLibrary::K2_SetTimer(this, "SwitchWorld", 1, false, false);
}

void ALevelSwitcherBox::SendToSave()
{
	UGameInstanceMain* GI = Cast<UGameInstanceMain>(GetGameInstance());
	if (GI && isSavingBox)
	{
		GI->SaveTemple();
	}
	GI->SaveGeneral();
}

