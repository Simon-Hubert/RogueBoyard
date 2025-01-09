// Fill out your copyright notice in the Description page of Project Settings.


#include "Room/RogueRoomPawn.h"

#include "Characters/RogueCharacter.h"
#include "Core/RogueGameMode.h"
#include "Room/RogueRoomSubsystem.h"


// Sets default values
ARogueRoomPawn::ARogueRoomPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARogueRoomPawn::BeginPlay()
{
	Super::BeginPlay();
	if(ARogueGameMode* GameMode =  Cast<ARogueGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->AddRoomPawn(this);
	}
	URogueRoomSubsystem* RoomSubsystem =  GetWorld()->GetSubsystem<URogueRoomSubsystem>();
	RoomSubsystem->RoomLoadedCallback(ERoomLoaded::Pawn);
}

// Called every frame
void ARogueRoomPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARogueRoomPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARogueRoomPawn::UnPossesRoom(ARogueCharacter* Character)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC)
	{
		return;
	}
	PC->UnPossess();
	PC->Possess(Character);
	Player = nullptr;
}

