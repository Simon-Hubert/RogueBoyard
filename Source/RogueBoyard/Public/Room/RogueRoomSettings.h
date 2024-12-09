// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "RogueRoomSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName="Room Generation Settings"))
class ROGUEBOYARD_API URogueRoomSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, Category="Rooms Settings")
	float MaxRoomSize;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Rooms Settings")
	int NumberOfRooms;

	UPROPERTY(Config, EditAnywhere, Category="Rooms Settings")
	TArray<TSoftObjectPtr<UWorld>> Rooms;

	UPROPERTY(Config, EditAnywhere, Category="Rooms Settings")
	TArray<TSoftObjectPtr<UWorld>> Lobbies;

};
