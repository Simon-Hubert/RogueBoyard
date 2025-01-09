// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RogueCharacterStateMachine.generated.h"

enum class ERogueCharacterStateID : uint8;
class URogueCharacterState;
class ARogueCharacter;

UCLASS()
class ROGUEBOYARD_API URogueCharacterStateMachine : public UObject
{
	GENERATED_BODY()

public:
	void Init(ARogueCharacter* InCharacter);
	void Tick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	ARogueCharacter* GetCharacter() const;

	UFUNCTION(BlueprintCallable)
	void ChangeState(ERogueCharacterStateID NextStateID);

	URogueCharacterState* GetState(ERogueCharacterStateID StateID);

	UPROPERTY(BlueprintReadWrite)
	FVector Sticks;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<URogueCharacterState> CurrentState;
	
	UPROPERTY(BlueprintReadOnly)
	ERogueCharacterStateID CurrentStateID;

	UPROPERTY(BlueprintReadOnly)
	ERogueCharacterStateID PreviousStateID;
	
protected:
	UPROPERTY()
	TObjectPtr<ARogueCharacter> Character;

	TArray<URogueCharacterState*> AllStates;
	
	void FindStates();
	void InitStates();

	
};
