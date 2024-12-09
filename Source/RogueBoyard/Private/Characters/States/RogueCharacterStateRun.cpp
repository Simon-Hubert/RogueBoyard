// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBoyard/Public/Characters/States/RogueCharacterStateRun.h"

#include "Camera/CameraActor.h"
#include "Characters/RogueCharacterStateMachine.h"
#include "Characters/States/RogueCharacterStateDash.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RogueBoyard/Public/Characters/RogueCharacter.h"


ERogueCharacterStateID URogueCharacterStateRun::GetStateID()
{
	return ERogueCharacterStateID::Run;
}

void URogueCharacterStateRun::StateEnter(ERogueCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->PlayAnimMontage(RunMontage);
}

void URogueCharacterStateRun::StateExit(ERogueCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void URogueCharacterStateRun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	FVector Pos = Character->GetActorLocation();
	if(!GetWorld()->LineTraceSingleByChannel(HitResult, Pos,FVector(Pos.X,Pos.Y,-1000),
	ECC_Visibility) && Character->GetCharacterMovement()->Velocity.Z < -100.f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Z: %f"),Character->GetCharacterMovement()->Velocity.Z );
		StateMachine->ChangeState(ERogueCharacterStateID::Fall);
	}
	if(StateMachine->Sticks.X == 0 && StateMachine->Sticks.Y == 0)
	{
		StateMachine->ChangeState(ERogueCharacterStateID::Idle);
	}
	if(InteractAnimTime >= 0)
	{
		InteractAnimTime -= DeltaTime;
		if(InteractAnimTime <= 0)
		{
			Character->PlayAnimMontage(RunMontage);
		}
	}
}

void URogueCharacterStateRun::Movement(float X, float Y)
{
	Super::Movement(X, Y);
	if(InteractAnimTime > 0) return;
	ACameraActor* Cam = Character->GetCamera();
	if(Cam != nullptr)
	{
		const FVector XAxisRelativeToCamera = Cam->GetActorRightVector();
		const FVector YAxisRelativeToCamera = Cam->GetActorForwardVector().RotateAngleAxis(Character->GetCamera()->GetActorRotation().Pitch , XAxisRelativeToCamera);
		Character->ForwardVector = YAxisRelativeToCamera * Y + XAxisRelativeToCamera * X;
		Character->AddMovementInput(Character->GetCamera()->GetActorRightVector(), X);
		Character->AddMovementInput(YAxisRelativeToCamera, Y);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Movement failed, no Camera Found"));
	}
}

bool URogueCharacterStateRun::Dash(float X, float Y)
{
	Super::Dash(X, Y);
	StateMachine->ChangeState(ERogueCharacterStateID::Dash);
	/*FVector Direction = FVector(X, Y, 0.0f);
	URogueCharacterStateDash* DashState = Cast<URogueCharacterStateDash>(StateMachine->CurrentState);
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

TArray<AActor*> URogueCharacterStateRun::Interact()
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

void URogueCharacterStateRun::Push()
{
	Super::Push();
	StateMachine->ChangeState(ERogueCharacterStateID::Pushing);
}
