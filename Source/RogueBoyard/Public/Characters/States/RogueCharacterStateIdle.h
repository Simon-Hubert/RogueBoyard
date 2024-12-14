﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueBoyard/Private/Characters/RogueCharacterState.h"
#include "RogueCharacterStateIdle.generated.h"


UCLASS(ClassGroup=(RogueCharacterState), meta=(BlueprintSpawnableComponent))
class ROGUEBOYARD_API URogueCharacterStateIdle : public URogueCharacterState
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	virtual ERogueCharacterStateID GetStateID() override;
	virtual void StateEnter(ERogueCharacterStateID PreviousStateID) override;
	virtual void StateExit(ERogueCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;

	virtual void Movement(float X, float Y) override;
	virtual bool Dash(float X, float Y) override;
	virtual TArray<AActor*> Interact() override;
	virtual void Push() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> IdleMontage;

private:
	FHitResult HitResult;
};
