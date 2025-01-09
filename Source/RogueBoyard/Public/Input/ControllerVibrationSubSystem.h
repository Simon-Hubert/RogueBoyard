// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ControllerVibrationSubSystem.generated.h"

/**
 * 
 */


UCLASS()
class ROGUEBOYARD_API UControllerVibrationSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void VibrationDegressive(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void VibrationProgressive(APlayerController* PlayerController);
	
	UFUNCTION(BlueprintCallable)
	void VibrationHeavyContinuous(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void VibrationHeavyQuick(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void VibrationLightQuick(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void VibrationLightContinuous(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void VibrationPulsing(APlayerController* PlayerController);
	
};
