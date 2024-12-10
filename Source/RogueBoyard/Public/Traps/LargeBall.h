// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueTrap.h"
#include "LargeBall.generated.h"

UENUM()
enum class ELargeBallState : uint8
{
	Locked = 0,
	MovingAlongPath,
	WaitForUserInputs,
};

UCLASS()
class ROGUEBOYARD_API ALargeBall : public ARogueTrap
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALargeBall();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap|LargeBall")
	float BallSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap|LargeBall")
	TArray<AActor*> Waypoints;

	UPROPERTY(EditAnywhere,Category = "Trap|LargeBall")
	float MoveStopRange = 10.f;
	
	UPROPERTY(EditAnywhere, Category = "Trap|LargeBall", meta=(Units="degrees"))
	float MoveAngleTolerance = 10.f;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BallMesh;

public:

	virtual void Tick(float DeltaTime) override;
	void MoveAlongPath(float DeltaTime);
	void HandleJoystickInput(FVector JoystickInput);
	int FindWaypointIndexFromDir(FVector JoystickInput);
	void EnableMovement();

	int8 CurrentWaypointIndex;
	FTimerHandle TimerHandle_MoveDelay;
	float MoveDelayTime;
	float BallRadius;
	ELargeBallState CurrentState = ELargeBallState::WaitForUserInputs;
	FVector MoveToDestination = FVector::ZeroVector;
};
