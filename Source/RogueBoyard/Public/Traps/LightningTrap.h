// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueTrap.h"
#include "LightningTrap.generated.h"

UCLASS()
class ROGUEBOYARD_API ALightningTrap : public ARogueTrap
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALightningTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Trap|LightningTrap")
	float Speed;

	FVector Movement;

	FVector RightVector;
	
	FVector ForwardVector;
	
	FVector NewLocation;

	FVector CurrentLocation;

private:
	void MoveOnXYDirection(float DeltaTime);
};
