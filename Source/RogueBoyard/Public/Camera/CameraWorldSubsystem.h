// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicCameraComponent.h"
#include "Characters/RogueCharacter.h"
#include "Subsystems/WorldSubsystem.h"
#include "CameraWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ROGUEBOYARD_API UCameraWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDist = 1000.f;

	UPROPERTY(BlueprintReadWrite)
	float ZoomDistanceBetweenTargetsMin = 300.f;

	UPROPERTY(BlueprintReadWrite)
	float ZoomDistanceBetweenTargetsMax = 1500.f;
	
	virtual void PostInitialize() override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override {return TStatId(); };

	UFUNCTION(BlueprintCallable)
	void AddFollowTarget(ARogueCharacter* FollowTarget);

	UFUNCTION(BlueprintCallable)
	void RemoveFollowTarget(ARogueCharacter* FollowTarget);

	UFUNCTION(BlueprintCallable)
	void ClearFollowTarget();

	UFUNCTION()
	void InitCameraZoomParameters(ACameraActor* CameraZoomMax, ACameraActor* CameraZoomMin);
	
	UFUNCTION(BlueprintCallable)
	void SetCamera(ACameraActor* NewCamera, ACameraActor* CameraZoomMaxIn, ACameraActor* CameraZoomMinIn);

	protected:
	UPROPERTY()
	TArray<ARogueCharacter*> FollowTargets;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACameraActor> CurrentCamera;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACameraActor> CameraZoomMax;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACameraActor> CameraZoomMin;

	TObjectPtr<UDynamicCameraComponent> CurrentCameraComp;

	FVector TargetLocation;
	FRotator x, xp, xd, y , yd;
	float xV, xpV, xdV, yV , ydV;
	float k1, k2, k3;
	
	void SecondOrderDynamics();
	
	float CameraDist;
	float DeltaRotationY, DeltaRotationZ;
	FRotator DefaultRotator;
	FVector DefaultTranslation;
	bool noDynamic = false;
	bool noZoom = false;
	
	void TickUpdateCameraPosition(float DeltaTime);
	void TickUpdateCameraZoom(float DeltaTime);

	FVector CalculateAveragePositionBetweenTargets();

	float CalculateGreatestDistanceBetweenTargets();
	
};
