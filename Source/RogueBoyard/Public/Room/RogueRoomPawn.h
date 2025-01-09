// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RogueRoomPawn.generated.h"

class ARogueCharacter;
class ARogueTrap;

UCLASS()
class ROGUEBOYARD_API ARogueRoomPawn : public APawn
{
	GENERATED_BODY()
#pragma region Unreal Default
public:
	// Sets default values for this pawn's properties
	ARogueRoomPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion Unreal Default

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ARogueTrap*> LeftStick;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ARogueTrap*> RightStick;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ARogueTrap*> LeftButton;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ARogueTrap*> RightButton;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ARogueTrap*> BottomButton;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ARogueTrap*> TopButton;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ARogueTrap*> LeftBumper;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ARogueTrap*> RightBumper;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ARogueTrap*> LeftTrigger;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ARogueTrap*> RightTrigger;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ARogueCharacter* Player;

	UFUNCTION(BlueprintCallable)
	void UnPossesRoom(ARogueCharacter* RogueCharacter);
	
};
