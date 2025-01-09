// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/WallBlade.h"

#include "LevelInstance/LevelInstanceTypes.h"


// Sets default values
AWallBlade::AWallBlade()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	Blade = CreateDefaultSubobject<UStaticMeshComponent>("Blade");
	Blade->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AWallBlade::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();
}

// Called every frame
void AWallBlade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveOnOneAxis(DeltaTime);
}

void AWallBlade::MoveOnOneAxis(const float& DeltaTime)
{
	if(bPlayedInit) {
		RightVector = GetActorRightVector();
        Direction = RightVector * JoystickInputAxis.X; 
        MovementDelta = Direction * MovementSpeed * DeltaTime;
        NewLocation	= Blade->GetComponentLocation() + MovementDelta;
        //NewLocation = GetActorLocation() + MovementDelta;
        DistanceFromStart = FVector::Dist(StartPosition, NewLocation);
        if (DistanceFromStart <= MaxDistance)
        {
        	Blade->SetWorldLocation(NewLocation);
        	//SetActorLocation(NewLocation);
        }
        else
        {
        	ClampedLocation = StartPosition + RightVector * MaxDistance * FMath::Sign(JoystickInputAxis.X);
        	Blade->SetWorldLocation(ClampedLocation);
        	//SetActorLocation(ClampedLocation);
        }
        DistanceTravelled = FVector::Dist(StartPosition, Blade->GetComponentLocation());
	}

}