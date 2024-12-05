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
}



// Called every frame
void ALargeBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleJoystickInput();
}

void ALargeBall::MoveTowardsTarget(float DeltaTime, FVector TargetLocation)
{
	if (TargetLocation != FVector::ZeroVector)
	{
		FVector Direction = TargetLocation - GetActorLocation();
		float Distance = Direction.Size();
		if (Distance < 10.f)
		{
			SetActorLocation(TargetLocation); 
			return;
		}
		Direction.Normalize();
		GetComponents()->
		FVector NewLocation = GetActorLocation() + (Direction * MoveSpeed * DeltaTime);
		SetActorLocation(NewLocation);
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

