// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ControllerVibrationSubSystem.h"

#include "Input/ControllerVibrationSettings.h"


void UControllerVibrationSubSystem::VibrationDegressive(APlayerController* PlayerController)
{

	//UForceFeedbackEffect * ForceFeedbackEffect = LoadObject<UForceFeedbackEffect>(nullptr, TEXT("ForceFeedbackEffect'/Game/RogueBoyard/Inputs/JoystickVibration/FFE_Degressive.FFE_Degressive'"));
	UForceFeedbackEffect* ForceFeedbackEffect = GetDefault<UControllerVibrationSettings>()->VibrationDegressiveFeedbackEffect.LoadSynchronous();
	if(ForceFeedbackEffect==nullptr||PlayerController==nullptr)return;
	PlayerController->ClientPlayForceFeedback(ForceFeedbackEffect);
}

void UControllerVibrationSubSystem::VibrationProgressive(APlayerController* PlayerController)
{
	//UForceFeedbackEffect * ForceFeedbackEffect = LoadObject<UForceFeedbackEffect>(nullptr, TEXT("ForceFeedbackEffect'/Game/RogueBoyard/Inputs/JoystickVibration/FFE_Progressive.FFE_Progressive'"));
	UForceFeedbackEffect* ForceFeedbackEffect = GetDefault<UControllerVibrationSettings>()->VibrationProgressiveFeedbackEffect.LoadSynchronous();
	if(ForceFeedbackEffect==nullptr||PlayerController==nullptr)return;
	PlayerController->ClientPlayForceFeedback(ForceFeedbackEffect);
}

void UControllerVibrationSubSystem::VibrationHeavyContinuous(APlayerController* PlayerController)
{
	//UForceFeedbackEffect * ForceFeedbackEffect = LoadObject<UForceFeedbackEffect>(nullptr, TEXT("ForceFeedbackEffect'/Game/RogueBoyard/Inputs/JoystickVibration/FFE_HeavyContinuous.FFE_HeavyContinuous'"));
	UForceFeedbackEffect* ForceFeedbackEffect = GetDefault<UControllerVibrationSettings>()->VibrationHeavyContinuousFeedbackEffect.LoadSynchronous();
	if(ForceFeedbackEffect==nullptr||PlayerController==nullptr)return;
	PlayerController->ClientPlayForceFeedback(ForceFeedbackEffect);
}

void UControllerVibrationSubSystem::VibrationHeavyQuick(APlayerController* PlayerController)
{
	//UForceFeedbackEffect * ForceFeedbackEffect = LoadObject<UForceFeedbackEffect>(nullptr, TEXT("ForceFeedbackEffect'/Game/RogueBoyard/Inputs/JoystickVibration/FFE_HeavyQuick.FFE_HeavyQuick'"));
	UForceFeedbackEffect* ForceFeedbackEffect = GetDefault<UControllerVibrationSettings>()->VibrationHeavyQuickFeedbackEffect.LoadSynchronous();
	if(ForceFeedbackEffect==nullptr||PlayerController==nullptr)return;
	PlayerController->ClientPlayForceFeedback(ForceFeedbackEffect);
}

void UControllerVibrationSubSystem::VibrationLightQuick(APlayerController* PlayerController)
{
	//UForceFeedbackEffect * ForceFeedbackEffect = LoadObject<UForceFeedbackEffect>(nullptr, TEXT("ForceFeedbackEffect'/Game/RogueBoyard/Inputs/JoystickVibration/FFE_LightQuick.FFE_LightQuick'"));
	 UForceFeedbackEffect* ForceFeedbackEffect = GetDefault<UControllerVibrationSettings>()->VibrationLightQuickFeedbackEffect.LoadSynchronous();
	if(ForceFeedbackEffect==nullptr||PlayerController==nullptr)return;
	PlayerController->ClientPlayForceFeedback(ForceFeedbackEffect);
}

void UControllerVibrationSubSystem::VibrationLightContinuous(APlayerController* PlayerController)
{
	//UForceFeedbackEffect * ForceFeedbackEffect = LoadObject<UForceFeedbackEffect>(nullptr, TEXT("ForceFeedbackEffect'/Game/RogueBoyard/Inputs/JoystickVibration/FFE_LightContinuous.FFE_LightContinuous'"));
	UForceFeedbackEffect* ForceFeedbackEffect = GetDefault<UControllerVibrationSettings>()->VibrationLightContinuousFeedbackEffect.LoadSynchronous();
	if(ForceFeedbackEffect==nullptr||PlayerController==nullptr)return;
	PlayerController->ClientPlayForceFeedback(ForceFeedbackEffect);
}

void UControllerVibrationSubSystem::VibrationPulsing(APlayerController* PlayerController)
{
	//UForceFeedbackEffect * ForceFeedbackEffect = LoadObject<UForceFeedbackEffect>(nullptr, TEXT("ForceFeedbackEffect'/Game/RogueBoyard/Inputs/JoystickVibration/FFE_Pulsing.FFE_Pulsing'"));
	UForceFeedbackEffect* ForceFeedbackEffect = GetDefault<UControllerVibrationSettings>()->VibrationPulsingFeedbackEffect.LoadSynchronous();
	if(ForceFeedbackEffect==nullptr||PlayerController==nullptr)return;
	PlayerController->ClientPlayForceFeedback(ForceFeedbackEffect);
}