// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueTrap.h"
#include "WolfTrap.generated.h"

UCLASS()
class ROGUEBOYARD_API AWolfTrap : public ARogueTrap
{
	GENERATED_BODY()

public:
	AWolfTrap();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
