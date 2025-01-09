#include "Room/Rooms/RogueRiddleRoom.h"

#include "Core/RogueGameMode.h"

ARogueRiddleRoom::ARogueRiddleRoom()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARogueRiddleRoom::BeginPlay()
{
	Super::BeginPlay();
}

void ARogueRiddleRoom::EndRoom()
{
	Super::EndRoom();
}

void ARogueRiddleRoom::RoomExit() {
	if(ARogueGameMode* GameMode = Cast<ARogueGameMode>(GetWorld()->GetAuthGameMode())) {
    	GameMode->EndBattleRoom();
    }
	Super::RoomExit();
}

void ARogueRiddleRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ThingsToValidate <= 0)
	{
		bHasRoomEnded = true;
		bLizardsHasWon = true;
		EndRoom();
	}
}

