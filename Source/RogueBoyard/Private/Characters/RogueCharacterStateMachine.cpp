// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBoyard/Public/Characters/RogueCharacterStateMachine.h"

#include "RogueCharacterState.h"
#include "RogueBoyard/Public/Characters/RogueCharacter.h"


void URogueCharacterStateMachine::Init(ARogueCharacter* InCharacter)
{
	Character = InCharacter;
	FindStates();
	InitStates();
	ChangeState(ERogueCharacterStateID::Waiting);
}

void URogueCharacterStateMachine::Tick(float DeltaTime)
{
	if(CurrentState == nullptr) return;
	CurrentState->StateTick(DeltaTime);
}

ARogueCharacter* URogueCharacterStateMachine::GetCharacter() const
{
	return Character;
}

URogueCharacterState* URogueCharacterStateMachine::GetState(ERogueCharacterStateID StateID)
{
	for(URogueCharacterState* State : AllStates)
	{
		if(StateID == State->GetStateID()) return State;
	}
	return nullptr;
}

void URogueCharacterStateMachine::FindStates()
{
	TArray<UActorComponent*> FoundComponents = Character
	->K2_GetComponentsByClass(URogueCharacterState::StaticClass());

	for(UActorComponent* StateComponent : FoundComponents)
	{
		URogueCharacterState* State = Cast<URogueCharacterState>(StateComponent);
		if(State == nullptr) continue;
		if(State->GetStateID() == ERogueCharacterStateID::None) continue;

		AllStates.Add(State);
	}
}

void URogueCharacterStateMachine::InitStates()
{
	for(URogueCharacterState* State : AllStates)
	{
		State->StateInit(this);
	}
}

void URogueCharacterStateMachine::ChangeState(ERogueCharacterStateID NextStateID)
{
	UE_LOG(LogTemp, Warning, TEXT("Change State"));
	URogueCharacterState* NextState = GetState(NextStateID);
	if(NextState == nullptr) return;
	if(NextStateID == CurrentStateID) return;
	if(CurrentState != nullptr) CurrentState->StateExit(NextStateID);

	PreviousStateID = CurrentStateID;
	CurrentStateID = NextStateID;
	CurrentState = NextState;

	if(CurrentState != nullptr) CurrentState->StateEnter(PreviousStateID);
		
}
