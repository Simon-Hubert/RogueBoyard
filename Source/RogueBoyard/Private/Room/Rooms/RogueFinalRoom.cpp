#include "Room/Rooms/RogueFinalRoom.h"

#include "Core/RogueGameMode.h"


ARogueFinalRoom::ARogueFinalRoom() {
	PrimaryActorTick.bCanEverTick = true;
	bBeginThePlay = false;
}

void ARogueFinalRoom::BeginPlay() {
	Super::BeginPlay();
}

void ARogueFinalRoom::EndRoom() {
	Super::EndRoom();
	if(ARogueGameMode* GameMode = Cast<ARogueGameMode>(GetWorld()->GetAuthGameMode())) {
		GameMode->GameEnd();
	}
}

void ARogueFinalRoom::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

