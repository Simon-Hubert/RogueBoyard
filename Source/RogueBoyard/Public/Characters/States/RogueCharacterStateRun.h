﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueBoyard/Private/Characters/RogueCharacterState.h"
#include "RogueCharacterStateRun.generated.h"


UCLASS(ClassGroup=(RogueCharacterState), meta=(BlueprintSpawnableComponent))
class ROGUEBOYARD_API URogueCharacterStateRun : public URogueCharacterState
{
	GENERATED_BODY()

public:
	virtual ERogueCharacterStateID GetStateID() override;
	virtual void StateEnter(ERogueCharacterStateID PreviousStateID) override;
	virtual void StateExit(ERogueCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;

	virtual void Movement(float X, float Y, ACameraActor* Camera) override;
	virtual bool Dash(float X, float Y) override;
	virtual TArray<AActor*> Interact() override;
	virtual bool Push(TArray<AActor*> Actors) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimationAsset> RunMontage;
};
