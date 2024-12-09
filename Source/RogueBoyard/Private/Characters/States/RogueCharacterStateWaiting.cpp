// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/RogueCharacterStateWaiting.h"
#include "Characters/RogueCharacter.h"
#include "Characters/RogueCharacterStateMachine.h"


ERogueCharacterStateID URogueCharacterStateWaiting::GetStateID()
{
	return ERogueCharacterStateID::Waiting;
}

void URogueCharacterStateWaiting::StateEnter(ERogueCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
}

void URogueCharacterStateWaiting::StateExit(ERogueCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

