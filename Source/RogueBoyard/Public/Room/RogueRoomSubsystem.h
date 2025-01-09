// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Subsystems/WorldSubsystem.h"
#include "RogueRoomSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextRoom);
DECLARE_MULTICAST_DELEGATE(FOnRoomFinishedLoading);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWasLastRoom);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoomLoaded);


UENUM()
enum ERoomLoaded
{
	Pawn,
	Manager
};

/**
 * 
 */
UCLASS()
class ROGUEBOYARD_API URogueRoomSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
public:
	UFUNCTION(BlueprintCallable)
	void NextRoom();
	void InitFirstRoom();
	UPROPERTY(BlueprintReadOnly)
	int ActiveRoomId = 0;

	void LoadNextRoom();
	void RoomLoadedCallback(ERoomLoaded Context);

	UPROPERTY(BlueprintReadWrite)
	bool bIsLoading = false;
	
	FOnRoomFinishedLoading OnRoomFinishedLoadingEvent;
	UPROPERTY(BlueprintAssignable)
	FOnRoomLoaded OnRoomLoadedEvent;

	UPROPERTY(BlueprintAssignable)
	FOnWasLastRoom OnWasLastRoomEvent;

	UPROPERTY(BlueprintAssignable)
	FOnNextRoom OnNextRoomEvent;
	
	UFUNCTION(BlueprintCallable)
	void UnloadPreviousRoom();

	UFUNCTION(BlueprintCallable)
	void UnloadAllRooms();
	
private:
	bool bPendingNextRoom = false;
	bool bIsNextRoomPawnLoaded = false;
	bool bIsNextRoomManagerLoaded = false;
	
	
	TArray<TSoftObjectPtr<UWorld>> Rooms;
	UPROPERTY()
	TArray<ULevelStreamingDynamic*> LoadedRooms;
	int LastLoadedRoomId = -1;
	FVector NextRoomPosition = FVector(0,0,0);
	
	void LoadRoomAtPosition(const TSoftObjectPtr<UWorld>& Room, const FVector& Position);
	void UnloadRoom(ULevelStreamingDynamic* Room);
	
	
};
