// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueTrap.h"
#include "Characters/RogueCharacter.h"
#include "Blackhole.generated.h"

UCLASS()
class ROGUEBOYARD_API ABlackhole : public ARogueTrap
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlackhole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AttractPlayers(float Attraction, ARogueCharacter* Player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttractionForce;
};
