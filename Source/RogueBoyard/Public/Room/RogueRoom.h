#pragma once

#include "CoreMinimal.h"
#include "RogueDoor.h"
#include "GameFramework/Actor.h"
#include "RogueRoom.generated.h"

class ARogueCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoomEnter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoomExit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoomBegin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoomEnd);

UCLASS()
class ROGUEBOYARD_API ARogueRoom : public AActor
{
	GENERATED_BODY()

public:
	ARogueRoom();

	
	/**
	 * Only for ChalengeRooms. Amount of coins given to the winning player(s)
	 */
	UPROPERTY(EditAnywhere)
	int RoomRewards;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ACameraActor* RoomCamera = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ACameraActor* RoomCameraZoomMax = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ACameraActor* RoomCameraZoomMin = nullptr;
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void RoomEnter();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="RoomEnter"))
	void ReceiveRoomEnter();

	UFUNCTION(BlueprintCallable)
	virtual void BeginRoom();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="BeginRoom"))
	void ReceiveBeginRoom();
	
	UFUNCTION(BlueprintCallable)
	virtual void EndRoom();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="EndRoom"))
	void ReceiveEndRoom();
	
	UFUNCTION(BlueprintCallable)
	virtual void RoomExit();
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="RoomExit"))
	void ReceiveRoomExit();

	UFUNCTION(BlueprintCallable)
	void PlacePlayers(TArray<ACharacter*> Players);

	UFUNCTION(BlueprintCallable)
	void PlacePlayer(ARogueCharacter* Player, int Index);

	FOnRoomBegin OnRoomBeginEvent;
	FOnRoomEnd OnRoomEndEvent;
	FOnRoomEnter OnRoomEnterEvent;
	FOnRoomExit OnRoomExitEvent;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	TArray<USceneComponent*> SpawnPoints;

	//TODO Mettre 4 Enter Doors, une par player, a chaque SpawnPoint;
	UPROPERTY(EditAnywhere)
	TObjectPtr<ARogueDoor> EnterDoor;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ARogueDoor> ExitDoor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxRoomTime = 120.0f;

	bool bBeginThePlay = true;
	
private:

	bool bHasRoomStarted = false;
	bool bHasRoomEnded = false;
	

};