// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/LargeBall.h"


// Sets default values
ALargeBall::ALargeBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALargeBall::BeginPlay()
{
	Super::BeginPlay();
	TargetPos = Ball->GetComponentLocation();
}



// Called every frame
void ALargeBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleJoystickInput();
	MoveTowardsTarget(DeltaTime,TargetPos);
}

void ALargeBall::MoveTowardsTarget(float DeltaTime, FVector TargetLocation)
{
	FVector Direction = (TargetLocation - Ball->GetComponentLocation()).GetSafeNormal();
	float Distance = (TargetLocation - Ball->GetComponentLocation()).Size();
	if (Distance <= Tolerance)
	{
		Ball->SetWorldLocation(TargetLocation);
		bArrived = true;
	}
	else
	{
		FVector Displacement = Direction * MoveSpeed * DeltaTime;
		FVector NewPosition = Ball->GetComponentLocation() + Displacement;
		Ball->SetWorldLocation(NewPosition);
	}
}

void ALargeBall::HandleJoystickInput()
{
	if (FMath::Abs(JoystickInputAxis.X) > FMath::Abs(JoystickInputAxis.Y))
	{
		if (JoystickInputAxis.X > InputThreshold)
		{
			JoystickMoveRight();
		}
		else if (JoystickInputAxis.X < -InputThreshold)
		{
			JoystickMoveLeft();
		}
	}
	else
	{
		if (JoystickInputAxis.Y > InputThreshold)
		{
			JoystickMoveUp();
		}
		else if (JoystickInputAxis.Y < -InputThreshold)
		{
			JoystickMoveDown();
		}
	}
}


void ALargeBall::JoystickMoveDown_Implementation()
{
}

void ALargeBall::JoystickMoveUp_Implementation()
{
}

void ALargeBall::JoystickMoveRight_Implementation()
{
}

void ALargeBall::JoystickMoveLeft_Implementation()
{
}

