// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LocalMultiplayerSubSystem.generated.h"

enum class ELocalMultiplayerInputMappingType : uint8;
/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API ULocalMultiplayerSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewPlayerJoined, int, PlayerIndex);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllPlayersJoined);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllPlayersReset);
public:

	UPROPERTY(BlueprintAssignable)
	FOnNewPlayerJoined OnNewPlayerJoinedEvent;
	UPROPERTY(BlueprintAssignable)
	FOnAllPlayersJoined OnAllPlayersJoined;
	UPROPERTY(BlueprintAssignable)
	FOnAllPlayersReset OnAllPlayersReset;
	UPROPERTY(BlueprintReadWrite)
	bool bIsInMenuSelection = false;

	UFUNCTION(BlueprintCallable)
	void ResetAllPlayers();
	UFUNCTION(BlueprintCallable)
	void CreateAndInitPlayers(ELocalMultiplayerInputMappingType MappingType);

	int GetAssignedPlayerIndexFromKeyboardProfileIndex(int KeyboardProfileIndex);

	int AssignNewPlayerToKeyboardProfile(int KeyboardProfileIndex);

	void AssignKeyboardMapping(int PlayerIndex, int KeyboardProfileIndex, ELocalMultiplayerInputMappingType MappingType) const;

	int GetAssignedPlayerIndexFromGamepadDeviceID(int DeviceID);

	int AssignNewPlayerToGamepadDeviceID(int DeviceID);

	void AssignGamepadInputMapping(int PlayerIndex, ELocalMultiplayerInputMappingType MappingType) const;

protected:
	UPROPERTY()
	uint8 LastAssignedPlayerIndex = -1;

	UPROPERTY()
	TMap<int, int> PlayerIndexFromKeyboardProfileIndex;

	UPROPERTY()
	TMap<int, int> PlayerIndexFromGamepadProfileIndex;
};
