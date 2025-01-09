// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapsInput.h"
#include "GameFramework/Actor.h"
#include "RogueTrap.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRogueTrapActivated);

UCLASS()
class ROGUEBOYARD_API ARogueTrap : public AActor, public ITrapsInput
{
	GENERATED_BODY()

public:
	
	ARogueTrap();

protected:
	
	virtual void BeginPlay() override;
	bool bPlayedInit = false;

#pragma region CoolDown
	UFUNCTION(BlueprintCallable)
	virtual void CoolDown(float TimeCooldown);

	UFUNCTION()
	virtual void CoolDownDelegate();
	
	float TimeCooldown;

	UPROPERTY(BlueprintReadOnly)
	bool canUse = true;
#pragma endregion CoolDown	
	
	UPROPERTY(EditAnywhere, Category = "Trap|Rotation")
	bool bCanRotate;

	UPROPERTY(EditAnywhere, Category = "Trap|Rotation")
	float ValueMinimalRotationJoystick;
	
	/**
	 * In degrees per second
	 */
	UPROPERTY(EditAnywhere, Category = "Trap|Rotation")
	float MaxRotationSpeed;
	
	UPROPERTY(EditAnywhere, Category = "Trap|Rotation")
	float Friction;

	UPROPERTY(EditAnywhere, Category = "Trap|Rotation")
	float Acceleration;
	
	void RotateTrap(float DeltaTime);

	virtual void Trigger_Implementation(const FVector& InputAxis) override;
	
	FVector JoystickInputAxis;

	UPROPERTY(BlueprintReadOnly)
	bool isActivated = false;
	
public:
	virtual void Tick(float DeltaTime) override;
	void ActiveTrap();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Active Trap"))
	void ReceiveActiveTrap();

	UFUNCTION(BlueprintCallable)
	virtual void Init();
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Init"))
	void ReceiveInit();

	UFUNCTION(BlueprintCallable)
	virtual void End();
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="End"))
	void ReceiveEnd();

private:
	//Rotation
	float CurrentRotationSpeed;
	
	FRotator NewRotation;
};
