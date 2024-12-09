#include "Room/RogueRoom.h"

#include "Characters/RogueCharacter.h"
#include "Characters/RogueCharacterStateID.h"
#include "Characters/RogueCharacterStateMachine.h"
#include "Core/RogueGameMode.h"
#include "GameFramework/Character.h"
#include "Room/RogueRoomSubsystem.h"

#define DEBUG(x) GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Cyan, x);

ARogueRoom::ARogueRoom()
{
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	SpawnPoints.Add(CreateDefaultSubobject<USceneComponent>("P1Spawnpoint"));
	SpawnPoints.Add(CreateDefaultSubobject<USceneComponent>("P2Spawnpoint"));
	SpawnPoints.Add(CreateDefaultSubobject<USceneComponent>("P3Spawnpoint"));
	SpawnPoints.Add(CreateDefaultSubobject<USceneComponent>("P4Spawnpoint"));
	for (USceneComponent* SpawnPoint : SpawnPoints)
	{
		SpawnPoint->SetupAttachment(Root);
	}
}

void ARogueRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bHasRoomStarted)
	{
		MaxRoomTime -= DeltaTime;
		if(MaxRoomTime <= 0 && !bHasRoomEnded)
		{
			EndRoom();
			bHasRoomEnded = true;
		}
	}
}

void ARogueRoom::RoomEnter()
{
	if(EnterDoor)
	{
		EnterDoor->Open();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1,1.0f,FColor::Red, "EnterDoor Not Set");
	}
	
	DEBUG("Room Entered");
	ReceiveRoomEnter();
	OnRoomEnterEvent.Broadcast();
}

void ARogueRoom::PlacePlayers(TArray<ACharacter*> Players)
{
	for (int i=0; i<Players.Num(); i++)
	{
		Players[i]->SetActorLocation(SpawnPoints[i]->GetComponentLocation());
	}
}

void ARogueRoom::PlacePlayer(ARogueCharacter* Player, const int Index)
{
	//TODO Guard Pour Index
	Player->SetActorTransform(SpawnPoints[Index]->GetComponentTransform());
}

void ARogueRoom::BeginPlay()
{
	Super::BeginPlay();
	if(bBeginThePlay) {
		if(ARogueGameMode* GameMode =  Cast<ARogueGameMode>(GetWorld()->GetAuthGameMode()))
        {
        	GameMode->AddRoomManager(this);
        }
        URogueRoomSubsystem* RoomSubsystem =  GetWorld()->GetSubsystem<URogueRoomSubsystem>();
        RoomSubsystem->RoomLoadedCallback(ERoomLoaded::Manager);
	}
	
}

void ARogueRoom::BeginRoom()
{
	if(EnterDoor)
	{
		EnterDoor->Close();
	}
	DEBUG("Room Begun");
	bHasRoomStarted = true;
	ReceiveBeginRoom();
	OnRoomBeginEvent.Broadcast();
	if(ARogueGameMode* GameMode =  Cast<ARogueGameMode>(GetWorld()->GetAuthGameMode()))
	{
		for (ARogueCharacter* Character : GameMode->Characters)
		{
			Character->StateMachine->ChangeState(ERogueCharacterStateID::Idle);
		}
	}
}

void ARogueRoom::EndRoom()
{
	if (ExitDoor)
	{
		ExitDoor->Open();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1,1.0f,FColor::Red, "ExitDoor Not Set");
	}
	DEBUG("Room Ended");
	ReceiveEndRoom();
	OnRoomEndEvent.Broadcast();
}

void ARogueRoom::RoomExit()
{
	if (ExitDoor)
	{
		ExitDoor->Close();
	}
	DEBUG("Room Exited");
	ReceiveRoomExit();
	OnRoomExitEvent.Broadcast();
}

