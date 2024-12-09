// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/RogueCharacterStateStun.h"
#include "AkGameplayStatics.h"
#include "Characters/RogueCharacter.h"
#include "Characters/RogueCharacterStateMachine.h"


ERogueCharacterStateID URogueCharacterStateStun::GetStateID()
{
	return ERogueCharacterStateID::Stun;
}

void URogueCharacterStateStun::StateEnter(ERogueCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->PlayAnimMontage(StunMontage, true);
	const FOnAkPostEventCallback NullCallBack;
	UAkGameplayStatics::PostEvent(
		VoiceEvent,
		nullptr,
		0,
		NullCallBack,
		false);
}

void URogueCharacterStateStun::StateExit(ERogueCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void URogueCharacterStateStun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	if(ParalTime > 0.f)
	{
		ParalTime -= DeltaTime;
		if(ParalTime <= 0.f)
		{
			if(StateMachine->Sticks.Length() != 0)
			{
				StateMachine->ChangeState(ERogueCharacterStateID::Run);
			}
			else
			{
				StateMachine->ChangeState(ERogueCharacterStateID::Idle);
			}
		}
	}
}

void URogueCharacterStateStun::Paralysis(float ParalysisTime)
{
	ParalTime = ParalysisTime;
}
