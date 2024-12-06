// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/Blackhole.h"


// Sets default values
ABlackhole::ABlackhole()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABlackhole::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlackhole::AttractPlayers(float Attraction, ARogueCharacter* Player)
{
	Attraction += 1;
	Attraction *= AttractionForce;
	FVector Dir = GetActorLocation() - Player->GetActorLocation();
	Dir.Normalize();
	UE_LOG(LogTemp, Warning, TEXT("Attraction: %f"), Dir * Attraction);
	Player->LaunchCharacter(Dir * Attraction, false, false);
}
