// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room/RogueRoom.h"
#include "RogueFinalRoom.generated.h"

UCLASS()
class ROGUEBOYARD_API ARogueFinalRoom : public ARogueRoom {
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ARogueFinalRoom();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndRoom() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
