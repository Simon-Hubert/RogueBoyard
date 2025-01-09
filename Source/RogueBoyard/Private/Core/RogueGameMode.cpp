// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RogueGameMode.h"

#include "LocalMultiplayerSettings.h"
#include "LocalMultiplayerSubSystem.h"
#include "Characters/RogueCharacter.h"
#include "Characters/RogueCharacterStateID.h"
#include "Characters/RogueCharacterStateMachine.h"
#include "Core/PlayerStatSubsystem.h"
#include "Economy/RoguePurse.h"
#include "Kismet/GameplayStatics.h"
#include "Room/RogueRoomPawn.h"
#include "Room/RogueRoomSubsystem.h"

void ARogueGameMode::BeginPlay()
{
	Super::BeginPlay();
	InitPlayers();
	InitCharacters();
	InitFirstRoom();
	InitStatSubsystem();
}


void ARogueGameMode::InitPlayers()
{
	const UGameInstance* GameInstance = GetGameInstance();
	if(GameInstance == nullptr) return;
	
	ULocalMultiplayerSubSystem* LocalMultiplayerSubSystem = GameInstance->GetSubsystem<ULocalMultiplayerSubSystem>();
	if(LocalMultiplayerSubSystem == nullptr) return;
	
	LocalMultiplayerSubSystem->CreateAndInitPlayers(ELocalMultiplayerInputMappingType::InGame);
}

void ARogueGameMode::InitCharacters()
{
	Characters.Init(nullptr, 4);
	for(int i = 0; i < 4; i++)
	{
		APawn* CharPawn =  UGameplayStatics::GetPlayerController(GetWorld(), i)->GetPawn();
		ARogueCharacter* Character = Cast<ARogueCharacter>(CharPawn);
		Characters[i] = Character;
		Character->PlayerIndex = i;
		Character->OnCharacterDeathEvent.AddDynamic(this, &ARogueGameMode::OnCharacterDeath);
		ReceiveInitCharacters(i);
	}
}

void ARogueGameMode::InitFirstRoom()
{
	URogueRoomSubsystem* RoomSubsystem = GetWorld()->GetSubsystem<URogueRoomSubsystem>();
	RoomSubsystem->OnRoomFinishedLoadingEvent.AddUObject(this, &ARogueGameMode::OnRoomLoaded);
	RoomSubsystem->InitFirstRoom();
	RoomSubsystem->OnWasLastRoomEvent.AddUniqueDynamic(this, &ARogueGameMode::LastRoomLoaded);
}

void ARogueGameMode::InitStatSubsystem() {
	UE_LOG(LogTemp, Warning, TEXT("Stat Subsystem try Init"));
	GetGameInstance()->GetSubsystem<UPlayerStatSubsystem>()->Init(Characters);
}

void ARogueGameMode::GiveRoomRewards(TArray<ARogueCharacter*> Winners) {
	for(ARogueCharacter* Character : Winners) {
		if(Character) {
			Character->Purse->Earn(ActiveRoom->RoomRewards);
		}
	}
}

void ARogueGameMode::OnCharacterDeath()
{
	int NbDeadPlayers = 0;
	for (const ARogueCharacter* Character : Characters)
	{
		if( Character->StateMachine->CurrentStateID == ERogueCharacterStateID::Dead)
		{
			NbDeadPlayers++;
			UE_LOG(LogTemp, Warning, TEXT("DeadCharacter, total : %d"), NbDeadPlayers)
		}
	}
	if(NbDeadPlayers >= 3)
	{
		ActiveRoom->bLizardsHasWon = false;
		ActiveRoom->EndRoom();
	}
}

void ARogueGameMode::OnRoomLoaded()
{
	if(!bIsFirstRoomLoaded)
	{
		bIsFirstRoomLoaded = true;
		StartLobbyRoom();
	}
}

void ARogueGameMode::GameEnd() {
	ReceiveGameEnd();
}

void ARogueGameMode::LastRoomLoaded() {
	bIsLastRoom = true;
}

void ARogueGameMode::PostLastRoom() {
	
	ReceivePostLastRoom();
}

ARogueCharacter* ARogueGameMode::GetRandomCharacter() {
	return Characters[FMath::RandRange(0,3)];
}

void ARogueGameMode::StartBattleRoom_Implementation()
{
	
}

void ARogueGameMode::EndBattleRoom_Implementation()
{

}

void ARogueGameMode::StartLobbyRoom_Implementation()
{
	
}

void ARogueGameMode::EndLobbyRoom_Implementation()
{
	
}

TArray<ARogueCharacter*> ARogueGameMode::GetAlivePlayers() {
	TArray<ARogueCharacter*> AliveCharacters;
	for(ARogueCharacter* Character : Characters) {
		if(Character->StateMachine->CurrentStateID != ERogueCharacterStateID::Dead) {
			AliveCharacters.Add(Character);
		}
	}
	return AliveCharacters;
}

void ARogueGameMode::AddRoom(ARogueRoomPawn* Pawn, ARogueRoom* Manager)
{
	AddRoomPawn(Pawn);
	AddRoomManager(Manager);
}

void ARogueGameMode::AddRoomPawn(ARogueRoomPawn* Pawn)
{
	if(!RoomPawns.Contains(Pawn) && Pawn)
	{
		RoomPawns.Add(Pawn);
	}
}

void ARogueGameMode::AddRoomManager(ARogueRoom* Manager)
{
	if(!RoomManagers.Contains(Manager) && Manager)
	{
		RoomManagers.Add(Manager);
	}
}
