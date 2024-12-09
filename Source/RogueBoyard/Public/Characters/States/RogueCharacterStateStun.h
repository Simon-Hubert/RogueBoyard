// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RogueCharacterState.h"
#include "RogueCharacterStateStun.generated.h"


class UAkAudioEvent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ROGUEBOYARD_API URogueCharacterStateStun : public URogueCharacterState
{
	GENERATED_BODY()
public:
	virtual ERogueCharacterStateID GetStateID() override;
	virtual void StateEnter(ERogueCharacterStateID PreviousStateID) override;
	virtual void StateExit(ERogueCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Paralysis(float ParalysisTime);

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> StunMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAkAudioEvent> VoiceEvent;

private:
	float ParalTime;
};
