// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueTrap.h"
#include "LargeBall.generated.h"

UCLASS()
class ROGUEBOYARD_API ALargeBall : public ARogueTrap
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALargeBall();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void HandleJoystickInput();

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 5.0f;

	UFUNCTION(BlueprintCallable)
	void MoveTowardsTarget(float DeltaTime, FVector TargetLocation);

	// Blueprint Native Events for Movement
	UFUNCTION(BlueprintNativeEvent)
	void JoystickMoveRight();

	UFUNCTION(BlueprintNativeEvent)
	void JoystickMoveLeft();

	UFUNCTION(BlueprintNativeEvent)
	void JoystickMoveUp();

	UFUNCTION(BlueprintNativeEvent)
	void JoystickMoveDown();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LargeBall|Input")
	float InputThreshold = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LargeBall")
	UStaticMeshComponent* Ball; 
};
