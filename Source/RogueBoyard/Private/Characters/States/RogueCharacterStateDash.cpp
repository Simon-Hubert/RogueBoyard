// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBoyard/Public/Characters/States/RogueCharacterStateDash.h"

#include "Camera/CameraActor.h"
#include "Characters/RogueCharacterStateMachine.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Items/Ballon.h"
#include "RogueBoyard/Public/Characters/RogueCharacter.h"

#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT(text), fstring))

ERogueCharacterStateID URogueCharacterStateDash::GetStateID()
{
	return ERogueCharacterStateID::Dash;
}

void URogueCharacterStateDash::StateEnter(ERogueCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Capsule = Cast<UCapsuleComponent>(Character->GetRootComponent());
	Sticks = StateMachine->Sticks;
	Sticks.Y = -Sticks.Y;
	FRotator CameraRotation = Character->GetCamera()->GetActorRotation();
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, TEXT("Enter Dash"));
	const FVector Dir = Sticks.RotateAngleAxis(CameraRotation.Yaw + 90, FVector::UpVector);
	Character->LaunchCharacter(Dir * ForceImpulse, true, false);
	DirPushBall = Dir * ForcePushBall;
	if(Capsule != nullptr) Capsule->OnComponentBeginOverlap.AddDynamic(this, &URogueCharacterStateDash::OverlapBegin);
	DashComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
		DashFX,
		Character->GetMesh(),
		"",
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::KeepRelativeOffset,
		true);
	DashComponent->SetVariableLinearColor(FName("LizzzardColor"), DashColor);
}

void URogueCharacterStateDash::StateExit(ERogueCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	GEngine->AddOnScreenDebugMessage(
		-1,
		2.f,
		FColor::Red,
		TEXT("Exit dash")
	);
}

void URogueCharacterStateDash::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	DashAnimTimeRemaining -= DeltaTime;
	GEngine->AddOnScreenDebugMessage(
	-1,
	2.f,
	FColor::Green,
	TEXT("tick dash")
	);
	Sticks = StateMachine->Sticks;
	if(DashAnimTimeRemaining <= 0.1f)
	{
		if(Sticks.Length() != 0)
		{
			StateMachine->ChangeState(ERogueCharacterStateID::Run);
		}
		else
		{
			StateMachine->ChangeState(ERogueCharacterStateID::Idle);
		}
	}
}


void URogueCharacterStateDash::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	ABallon* ball = Cast<ABallon>(OtherActor);
	if(ball != nullptr)
	{
		ball->bIsPushed = true;
		ball->AddImpulse(DirPushBall, false);
	}
}
