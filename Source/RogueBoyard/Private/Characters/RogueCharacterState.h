﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueBoyard/Public/Characters/RogueCharacterStateID.h"
#include "Components/ActorComponent.h"
#include "RogueCharacterState.generated.h"
class ARogueCharacter;
class URogueCharacterStateMachine;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ROGUEBOYARD_API URogueCharacterState : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URogueCharacterState();

	virtual ERogueCharacterStateID GetStateID();
	virtual void StateInit(URogueCharacterStateMachine* InStateMachine);
	virtual void StateEnter(ERogueCharacterStateID PreviousStateID);
	virtual void StateExit(ERogueCharacterStateID NextStateID);
	virtual void StateTick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	virtual void Movement(float X, float Y, ACameraActor* Camera = nullptr);
	UFUNCTION(BlueprintCallable)
	virtual bool Dash(float X, float Y);
	UFUNCTION(BlueprintCallable)
	virtual TArray<AActor*> Interact();
	UFUNCTION(BlueprintCallable)
	virtual bool Push(TArray<AActor*> Actors);
	UFUNCTION(BlueprintCallable)
	virtual void Resurrect();
	
	

protected:
	UPROPERTY()
	TObjectPtr<ARogueCharacter> Character;

	UPROPERTY()
	TObjectPtr<URogueCharacterStateMachine> StateMachine;
};
