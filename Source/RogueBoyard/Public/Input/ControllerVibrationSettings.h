// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ControllerVibrationSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta= (DisplayName="Controller Vibration Settings"))
	
class ROGUEBOYARD_API UControllerVibrationSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="Controller Vibration Settings")
	TSoftObjectPtr<UForceFeedbackEffect> VibrationDegressiveFeedbackEffect;
	UPROPERTY(Config, EditAnywhere, Category="Controller Vibration Settings")
	TSoftObjectPtr<UForceFeedbackEffect> VibrationProgressiveFeedbackEffect;
	UPROPERTY(Config, EditAnywhere, Category="Controller Vibration Settings")
	TSoftObjectPtr<UForceFeedbackEffect>  VibrationHeavyContinuousFeedbackEffect;
	UPROPERTY(Config, EditAnywhere, Category="Controller Vibration Settings")
	TSoftObjectPtr<UForceFeedbackEffect>  VibrationHeavyQuickFeedbackEffect;
	UPROPERTY(Config, EditAnywhere, Category="Controller Vibration Settings")
	TSoftObjectPtr<UForceFeedbackEffect>  VibrationLightQuickFeedbackEffect;
	UPROPERTY(Config, EditAnywhere, Category="Controller Vibration Settings")
	TSoftObjectPtr<UForceFeedbackEffect>  VibrationLightContinuousFeedbackEffect;
	UPROPERTY(Config, EditAnywhere, Category="Controller Vibration Settings")
	TSoftObjectPtr<UForceFeedbackEffect>  VibrationPulsingFeedbackEffect;
	
};
