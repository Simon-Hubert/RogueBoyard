// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueTrap.h"
#include "Millstone.generated.h"

UCLASS()
class ROGUEBOYARD_API AMillstone : public ARogueTrap
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMillstone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BLueprintNativeEvent, BlueprintCallable)
	void RotateMillstone(float DeltaTime,FVector InputAxis);
};
