// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/LargeBall.h"

#include "Kismet/KismetMathLibrary.h"


ALargeBall::ALargeBall()
{
	PrimaryActorTick.bCanEverTick = true;
	MoveDelayTime = 1.0f;
}


void ALargeBall::BeginPlay()
{
	Super::BeginPlay();
	FVector Origin, BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	BallRadius = BoxExtent.Z;
	CurrentWaypointIndex = 0;
	CurrentState = ELargeBallState::WaitForUserInputs;
	CameraRightVector = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorRightVector();
	
	CameraForwardVector = CameraRightVector.RotateAngleAxis(-90, FVector(0, 0, 1));
	InitPositionBall();
}


void ALargeBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentState)
	{
	case ELargeBallState::Locked:
		//UE_LOG(LogTemp, Error, TEXT("Locked"));
		break;

	case ELargeBallState::MovingAlongPath:
		//UE_LOG(LogTemp, Error, TEXT("Move along Path"));
		MoveAlongPath(DeltaTime);
		break;

	case ELargeBallState::WaitForUserInputs:
		//UE_LOG(LogTemp, Error, TEXT("WaitForUserInputs"));
		HandleJoystickInput(JoystickInputAxis);
		break;
	}
}

void ALargeBall::MoveAlongPath(float DeltaTime)
{
	if(bPlayedInit)
	{
		FVector CurrentPosition = GetActorLocation();
		FVector Direction = (MoveToDestination - CurrentPosition);
		Direction.Normalize();

		FVector NewPosition = CurrentPosition + Direction * BallSpeed * DeltaTime;
		SetActorLocation(NewPosition);

		if(!bDistanceCalculated)
		{
			DistanceToTravel =  FVector::Distance(CurrentPosition, NewPosition);
			bDistanceCalculated = true;
		}
		float RotationAngle = DistanceToTravel / (2 * PI * BallRadius);  // Angle en radians

		// Calculer l'axe de rotation perpendiculaire à la direction du mouvement
		FVector RightAxis = FVector::CrossProduct(Direction, FVector(0, 0, 1));
		RightAxis.Normalize();

		// Si le produit vectoriel donne un axe nul, la direction est parfaitement verticale,
		if (RightAxis.IsNearlyZero())
		{
			RightAxis = FVector(1, 0, 0);
		}
		FRotator RotatorDirection(0,90 , 0);
		FVector VectorRotatorDirection = RotatorDirection.RotateVector(Direction);
		// Créer la rotation autour de l'axe perpendiculaire à la direction du mouvement
		FQuat RotationQuat = FQuat(VectorRotatorDirection, RotationAngle);
		FQuat NewRotationBall =RotationQuat *  GetActorQuat();
		SetActorRotation(NewRotationBall);
	

		if (FVector::Distance(CurrentPosition, MoveToDestination) < MoveStopRange)
		{
			bDistanceCalculated = false;
			CurrentState = ELargeBallState::WaitForUserInputs;
		}
	}
}

void ALargeBall::HandleJoystickInput(FVector JoystickInput)
{
	int NextIndex = FindWaypointIndexFromDir(JoystickInput);
	if (NextIndex < 0) return;
	
	CurrentWaypointIndex = NextIndex;
	MoveToDestination = Waypoints[CurrentWaypointIndex]->GetActorLocation();
	if(CurrentState != ELargeBallState::Locked)
	{
		CurrentState = ELargeBallState::Locked;
		if(MoveDelayTime < 0.1f)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveDelay, this, &ALargeBall::EnableMovement, 0.1f,false);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveDelay, this, &ALargeBall::EnableMovement, MoveDelayTime,false);
		}
		
	}
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
	FRotator Rotator(180.0f, -90.0f, 0.0f);
	FRotator RotatorCamera(0.0f,GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Yaw, 0.0f);
	PreviousWaypointDir = Rotator.RotateVector(PreviousWaypointDir);
	PreviousWaypointDir = RotatorCamera.RotateVector(PreviousWaypointDir);
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
	NextWaypointDir = Rotator.RotateVector(NextWaypointDir);
	NextWaypointDir = RotatorCamera.RotateVector(NextWaypointDir);
	NextWaypointDir.Normalize();

	float NextDotProduct = FVector::DotProduct(NextWaypointDir, JoystickInput);
	float NextRadAngle = FMath::Acos(NextDotProduct);
	float NextDegAngle = FMath::RadiansToDegrees(NextRadAngle);

	if (NextDegAngle < MoveAngleTolerance)
	{
		return NextWaytpointIndex;
	}

	//No Waypoints found if not inside next or previous angle tolerance
	return -1;
}

void ALargeBall::InitPositionBall()
{
	if(Waypoints.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("LargeBall - List Waypoint Empty"));
		return;
	}
	SetActorLocation( Waypoints[CurrentWaypointIndex]->GetActorLocation());
}


void ALargeBall::EnableMovement()
{
	CurrentState = ELargeBallState::MovingAlongPath;
}