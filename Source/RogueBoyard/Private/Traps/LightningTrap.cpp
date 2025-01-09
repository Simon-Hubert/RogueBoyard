// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/LightningTrap.h"


// Sets default values
ALightningTrap::ALightningTrap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALightningTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightningTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveOnXYDirection(DeltaTime);
}

void ALightningTrap::MoveOnXYDirection(float DeltaTime)
{
	if(bPlayedInit) {
			RightVector = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorRightVector();
        	ForwardVector = RightVector.RotateAngleAxis(-90, FVector(0, 0, 1));
        	Movement = JoystickInputAxis * Speed * DeltaTime;
        	NewLocation = GetActorLocation() + (RightVector * Movement.X) + (ForwardVector * Movement.Y);
        	SetActorLocation(NewLocation);
	}
}