// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSwitcherBox.h"

#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
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
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor)) SwitchWorld();
}

void ALevelSwitcherBox::SwitchWorld()
{
	FString Options = "";
	LevelToOpen.LoadSynchronous();
	if (!LevelToOpen.IsNull()) UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),LevelToOpen , true, Options);
	UE_LOG(LogTemp, Warning, TEXT("%d"), LevelToOpen.IsValid());
}

