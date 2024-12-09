// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ERogueCharacterStateID : uint8
{
	None = 0,
	Idle,
	Run,
	Dash,
	Pushing,
	Pushed,
	Fall,
	Waiting,
	Stun,
	Dead
};
