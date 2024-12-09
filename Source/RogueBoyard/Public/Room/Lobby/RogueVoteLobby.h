#pragma once

#include "CoreMinimal.h"
#include "RogueLobby.h"
#include "RogueVoteZone.h"
#include "RogueVoteLobby.generated.h"

UCLASS()
class ROGUEBOYARD_API ARogueVoteLobby : public ARogueLobby
{
	GENERATED_BODY()

public:
	ARogueVoteLobby();
	virtual void Tick(float DeltaTime) override;

	virtual void EndRoom() override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	float ElapsedTime = 0.0f;
	
	UPROPERTY(BlueprintReadOnly)
    bool bIsVoteActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float VoteTimer = 10.0f;
	
private:
	
	UPROPERTY(EditAnywhere)
	bool bShouldVoteTimerReset = false;
	
	UPROPERTY(EditAnywhere)
	ARogueVoteZone* VoteZone;
	
	UFUNCTION()
	void PlayerEnteredVoteZone();

	UFUNCTION()
	void AllPlayerExitVoteZone();
};
