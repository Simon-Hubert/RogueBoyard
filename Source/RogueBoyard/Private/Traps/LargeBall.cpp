// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/LargeBall.h"

#include "Kismet/KismetMathLibrary.h"


ALargeBall::ALargeBall()
{
	PrimaryActorTick.bCanEverTick = true;
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	RootComponent = BallMesh;
	MoveDelayTime = 1.0f;
}


void ALargeBall::BeginPlay()
{
	Super::BeginPlay();
	FVector BoxExtent;
	BallMesh->GetLocalBounds(BoxExtent, BoxExtent);
	BallRadius = BoxExtent.Size();
	CurrentWaypointIndex = 0;
	CurrentState = ELargeBallState::WaitForUserInputs;
}


void ALargeBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentState)
	{
	case ELargeBallState::Locked:
		//Do nothing here
		break;

	case ELargeBallState::MovingAlongPath:
		MoveAlongPath(DeltaTime);
		break;

	case ELargeBallState::WaitForUserInputs:
		HandleJoystickInput(JoystickInputAxis);
		break;
	}
}

void ALargeBall::MoveAlongPath(float DeltaTime)
{
	FVector CurrentPosition = GetActorLocation();
	FVector Direction = (MoveToDestination - CurrentPosition);
	Direction.Normalize();

	FVector NewPosition = CurrentPosition + Direction * BallSpeed * DeltaTime;
	SetActorLocation(NewPosition);

	float AngularVelocity = BallSpeed / BallRadius;
	FQuat RotationQuat = FQuat(Direction, AngularVelocity * DeltaTime);
	BallMesh->AddLocalRotation(RotationQuat);

	if (FVector::Distance(CurrentPosition, NewPosition) < MoveStopRange)
	{
		CurrentState = ELargeBallState::WaitForUserInputs;
	}
}

void ALargeBall::HandleJoystickInput(FVector JoystickInput)
{
	int NextIndex = FindWaypointIndexFromDir(JoystickInput);
	if (NextIndex < 0) return;

	CurrentWaypointIndex = NextIndex;
	MoveToDestination = Waypoints[CurrentWaypointIndex]->GetActorLocation();
	CurrentState = ELargeBallState::Locked;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveDelay, this, &ALargeBall::EnableMovement, MoveDelayTime,
	                                       false);
}

int ALargeBall::FindWaypointIndexFromDir(FVector JoystickInput)
{
	JoystickInput.Normalize();
	if(Waypoints.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("LargeBall - List Waypoint Empty"));
		return -1;
	}
	AActor* CurrentWaypoint = Waypoints[CurrentWaypointIndex];

	//Check if previous waypoint inside angle tolerance
	int PreviousWaypointIndex = CurrentWaypointIndex - 1;
	if (PreviousWaypointIndex < 0)
	{
		PreviousWaypointIndex = Waypoints.Num() - 1;
	}

	AActor* PreviousWaypoint = Waypoints[PreviousWaypointIndex];

	FVector PreviousWaypointDir = PreviousWaypoint->GetActorLocation() - CurrentWaypoint->GetActorLocation();
	PreviousWaypointDir.Normalize();

	float PreviousDotProduct = FVector::DotProduct(PreviousWaypointDir, JoystickInput);
	float PreviousRadAngle = FMath::Acos(PreviousDotProduct);
	float PreviousDegAngle = FMath::RadiansToDegrees(PreviousRadAngle);

	if (PreviousDegAngle < MoveAngleTolerance)
	{
		return PreviousWaypointIndex;
	}

	//Check if next waypoint inside angle tolerance
	int NextWaytpointIndex = CurrentWaypointIndex + 1;
	if (NextWaytpointIndex >= Waypoints.Num())
	{
		NextWaytpointIndex = 0;
	}

	AActor* NextWayPoint = Waypoints[NextWaytpointIndex];

	FVector NextWaypointDir = NextWayPoint->GetActorLocation() - CurrentWaypoint->GetActorLocation();
	NextWaypointDir.Normalize();

	float NextDotProduct = FVector::DotProduct(NextWaypointDir, JoystickInputAxis);
	float NextRadAngle = FMath::Acos(NextDotProduct);
	float NextDegAngle = FMath::RadiansToDegrees(NextRadAngle);

	if (NextDegAngle < MoveAngleTolerance)
	{
		return NextWaytpointIndex;
	}

	//No Waypoints found if not inside next or previous angle tolerance
	return -1;
}


void ALargeBall::EnableMovement()
{
	CurrentState = ELargeBallState::MovingAlongPath;
}
