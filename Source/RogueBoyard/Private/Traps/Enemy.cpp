// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/Enemy.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitialPosition = GetActorLocation();
	SetLifeSpan(LifeSpan);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::Push(TArray<AActor*> Actors)
{
	for (AActor* Actor : Actors)
	{
		FVector Dir = Actor->GetActorLocation() - GetActorLocation();
		Dir.Normalize();
		UPushableComponent* pushComp = Cast<UPushableComponent>(Actor->GetComponentByClass(UPushableComponent::StaticClass()));
		if(pushComp != nullptr) pushComp->Push(Dir, PushForce);
	}
}

void AEnemy::SearchMovement(float DeltaTime)
{
	CurrentTime += DeltaTime * SearchMoveSpeed;
	NewPosition = InitialPosition;
	NewPosition.X += InitialPosition.X + MoveAmplitudeX * FMath::Sin(CurrentTime);
	NewPosition.Y += InitialPosition.Y + MoveAmplitudeY * FMath::Sin(2 * CurrentTime);
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), NewPosition));
	SetActorLocation(NewPosition);
}

void AEnemy::MoveToPlayer(AActor* Player,float DeltaTime)
{
	CurrentLocation = GetActorLocation();
	TargetLocation = Player->GetActorLocation();
	Direction = TargetLocation - CurrentLocation;
	Direction.Normalize();
	NewLocation = CurrentLocation + Direction * MoveSpeed * DeltaTime;
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FVector(NewLocation.X,NewLocation.Y,GetActorLocation().Z)));
	SetActorLocation(FVector(NewLocation.X,NewLocation.Y,GetActorLocation().Z));
}

