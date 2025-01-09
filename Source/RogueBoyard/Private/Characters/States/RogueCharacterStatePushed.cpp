// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/RogueCharacterStatePushed.h"

#include "AkGameplayStatics.h"
#include "Characters/RogueCharacter.h"
#include "Characters/RogueCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Input/ControllerVibrationSubSystem.h"
#include "Kismet/GameplayStatics.h"

ERogueCharacterStateID URogueCharacterStatePushed::GetStateID()
{
	return ERogueCharacterStateID::Pushed;
}

void URogueCharacterStatePushed::StateEnter(ERogueCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->OnCharacterPushedEvent.Broadcast();
	Character->GetMesh()->PlayAnimation(PushedMontage, false);
	const FOnAkPostEventCallback NullCallBack;
	UAkGameplayStatics::PostEvent(
		VoiceEvent,
		nullptr,
		0,
		NullCallBack,
		false);

	Character->OnPushed();
}

void URogueCharacterStatePushed::StateExit(ERogueCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	GEngine->AddOnScreenDebugMessage(
		-1, 3.0f, FColor::Red, TEXT("Exit Pushed"));
}

void URogueCharacterStatePushed::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	DelayTime += DeltaTime;
	FVector Velocity = Character->GetCharacterMovement()->Velocity;
	FVector Pos = Character->GetActorLocation();
	if(!GetWorld()->LineTraceSingleByChannel(HitResult, Pos,FVector(Pos.X,Pos.Y,-1000),
		ECC_Visibility))
	{
		Character->GetCharacterMovement()->Velocity = FVector(
		Velocity.X * 0.9f,
		Velocity.Y * 0.9f,
		Velocity.Z);
		if((Velocity.X <= 50 && Velocity.X >= -50) && (Velocity.Y <= 50 && Velocity.Y >= -50) && Velocity.Z < -200)
		{
			StateMachine->ChangeState(ERogueCharacterStateID::Fall);
		}
		
	}

	if(Character->GetVelocity().Length() == 0 && DelayTime >= 0.3f)
	{
		Character->TriggerFinishPushed();
		DelayTime = 0.f;
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
