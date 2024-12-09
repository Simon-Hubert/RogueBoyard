// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "RogueBoyard/Private/Characters/RogueCharacterState.h"
#include "RogueCharacterStateDash.generated.h"


UCLASS(ClassGroup=(RogueCharacterState), meta=(BlueprintSpawnableComponent))
class ROGUEBOYARD_API URogueCharacterStateDash : public URogueCharacterState
{
	GENERATED_BODY()

public:

	virtual ERogueCharacterStateID GetStateID() override;
	virtual void StateEnter(ERogueCharacterStateID PreviousStateID) override;
	virtual void StateExit(ERogueCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> DashMontage;
	
	UPROPERTY(EditAnywhere)
	float ForceImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DashCoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ForcePushBall;
	
private:
	FVector Sticks;
	float DashAnimTimeRemaining;
	FVector DirPushBall;

	UPROPERTY()
	UCapsuleComponent* Capsule;

	UFUNCTION(BlueprintCallable)
	void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult);
};
