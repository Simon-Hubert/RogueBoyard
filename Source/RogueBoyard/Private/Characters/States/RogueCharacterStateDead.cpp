// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/RogueCharacterStateDead.h"

#include "Camera/CameraWorldSubsystem.h"
#include "Characters/RogueCharacter.h"
#include "Characters/RogueCharacterStateMachine.h"


ERogueCharacterStateID URogueCharacterStateDead::GetStateID()
{
	return ERogueCharacterStateID::Dead;
}

void URogueCharacterStateDead::StateEnter(ERogueCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	GetWorld()->GetSubsystem<UCameraWorldSubsystem>()->RemoveFollowTarget(Character);
	Character->PlayAnimMontage(DeadMontage);
	if(ResurectMontage) ResurectAnimTimeRemaining = ResurectMontage->GetPlayLength();
	Character->OnCharacterDeathEvent.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Enter Dead"));
}

void URogueCharacterStateDead::StateExit(ERogueCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->CurrentLives = Character->LivesMAX;
	//UE_LOG(LogTemp, Warning, TEXT("Character Resurected without permission"))
	bRespawned = false;
	UE_LOG(LogTemp, Warning, TEXT("Exit Dead"));
}

void URogueCharacterStateDead::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
}

void URogueCharacterStateDead::Resurrect()
{
	Super::Resurrect();
	UE_LOG(LogTemp, Warning, TEXT("Character Resurected"))
	Character->PlayAnimMontage(DeadMontage);
}
