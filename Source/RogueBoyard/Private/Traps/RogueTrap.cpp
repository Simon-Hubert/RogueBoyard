// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBoyard/Public/Traps/RogueTrap.h"
#include "Math/UnrealMathUtility.h"
#include <cmath>

ARogueTrap::ARogueTrap()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARogueTrap::BeginPlay()
{
	Super::BeginPlay();
}

void ARogueTrap::CoolDown(float TimeCooldownIn)
{
	FTimerManager& Tm = GetWorldTimerManager();
	FTimerHandle TimerHandle;
	FTimerDelegate Delegate;
	TimeCooldown = TimeCooldownIn;
	canUse = false;
	Delegate.BindUFunction(this, "CoolDownDelegate");
	Tm.SetTimer(TimerHandle, Delegate, 0.5f, true);
}

void ARogueTrap::CoolDownDelegate()
{
	TimeCooldown -= 0.5f;
	UE_LOG(LogTemp, Warning, TEXT("BLBLBLBLBL"));
	if(TimeCooldown <=0.f)
	{

		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
		canUse = true;
	}
}

// Called every frame
void ARogueTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateTrap(DeltaTime);
}

void ARogueTrap::ActiveTrap()
{
	isActivated = true;
	ReceiveActiveTrap();
}

void ARogueTrap::RotateTrap(float DeltaTime)
{
	if (bCanRotate)
	{
		if(FMath::Abs(JoystickInputAxis.X) > ValueMinimalRotationJoystick)
		{
			CurrentRotationSpeed += JoystickInputAxis.X * Acceleration * DeltaTime;
			CurrentRotationSpeed = FMath::Clamp(CurrentRotationSpeed, -MaxRotationSpeed, MaxRotationSpeed);
		}
		CurrentRotationSpeed -= CurrentRotationSpeed * Friction * DeltaTime;
		NewRotation = GetActorRotation();
		NewRotation.Yaw += CurrentRotationSpeed * DeltaTime;
		SetActorRotation(NewRotation);
	}
}

void ARogueTrap::Trigger_Implementation(const FVector& InputAxis)
{
	JoystickInputAxis = InputAxis;
}

