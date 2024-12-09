// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBoyard/Public/Characters/States/RogueCharacterStateIdle.h"

#include "Characters/RogueCharacterStateMachine.h"
#include "Characters/States/RogueCharacterStateDash.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RogueBoyard/Public/Characters/RogueCharacter.h"


ERogueCharacterStateID URogueCharacterStateIdle::GetStateID()
{
	return ERogueCharacterStateID::Idle;
}

void URogueCharacterStateIdle::StateEnter(ERogueCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	GEngine->AddOnScreenDebugMessage(
	-1,
	2.f,
	FColor::Green,
	TEXT("Enter Idle"));
	float playRate = FMath::RandRange(0.8f, 1.2f);
	Character->PlayAnimMontage(IdleMontage, playRate);
}

void URogueCharacterStateIdle::StateExit(ERogueCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	GEngine->AddOnScreenDebugMessage(
	-1,
	0.1f,
	FColor::Red,
	TEXT("Exit idle")
	);
}

void URogueCharacterStateIdle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	FVector Pos = Character->GetActorLocation();
	if(!GetWorld()->LineTraceSingleByChannel(HitResult, Pos,FVector(Pos.X,Pos.Y,-1000),
	ECC_Visibility) && Character->GetCharacterMovement()->Velocity.Z < -100.f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Z: %f"),Character->GetCharacterMovement()->Velocity.Z );
		StateMachine->ChangeState(ERogueCharacterStateID::Fall);
	}
	if(InteractAnimTime >= 0)
	{
		InteractAnimTime -= DeltaTime;
		if(InteractAnimTime <= 0)
		{
			float playRate = FMath::RandRange(0.8f, 1.2f);
			Character->PlayAnimMontage(IdleMontage, playRate);
		}
	}
}

void URogueCharacterStateIdle::Movement(float X, float Y)
{
	Super::Movement(X, Y);
	if(InteractAnimTime > 0)
	GEngine->AddOnScreenDebugMessage(
	-1,
	2.f,
	FColor::Cyan,
	TEXT("Moving")
	);
	StateMachine->ChangeState(ERogueCharacterStateID::Run);
}

bool URogueCharacterStateIdle::Dash(float X, float Y)
{
	Super::Dash(X, Y);
	StateMachine->ChangeState(ERogueCharacterStateID::Dash);
	FVector Direction = FVector(X, Y, 0.0f);
	/*URogueCharacterStateDash* DashState = Cast<URogueCharacterStateDash>(StateMachine->CurrentState);
	if(Direction.IsZero())
	{
		Direction = Character->GetMesh()->GetRightVector() * DashState->ForceImpulse;
		Character->LaunchCharacter(Direction, true, false);
	}
	else
	{
		Character->LaunchCharacter(Direction * DashState->ForceImpulse,	 true, false);
	}*/
	return true;
}

TArray<AActor*> URogueCharacterStateIdle::Interact()
{
	Super::Interact();
	InteractAnimTime = InteractMontage->GetPlayLength();
	Character->PlayAnimMontage(InteractMontage);
	TArray<AActor*> OverlappingActors;
	Character->Box->GetOverlappingActors(OverlappingActors);
	GEngine->AddOnScreenDebugMessage(
	-1,
	2.f,
	FColor::Cyan,
	TEXT("InteractC++")
	);
	return OverlappingActors;
}

void URogueCharacterStateIdle::Push()
{
	Super::Push();
	StateMachine->ChangeState(ERogueCharacterStateID::Pushing);
	return StateMachine->CurrentState->Push();
}


