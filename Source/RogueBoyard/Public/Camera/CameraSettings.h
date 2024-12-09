// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CameraSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName="Camera Dynamic Settings"))
class ROGUEBOYARD_API UCameraSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="Camera Settings")
	float f;
	UPROPERTY(Config, EditAnywhere, Category="Camera Settings")
	float z;
	UPROPERTY(Config, EditAnywhere, Category="Camera Settings")
	float r;
};
