#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerStatSubsystem.generated.h"

class URoguePurse;
class ARogueCharacter;

UCLASS()
class ROGUEBOYARD_API UPlayerStatSubsystem : public UGameInstanceSubsystem {
	GENERATED_BODY()

public:
	void Init(TArray<ARogueCharacter*> Characters);

	UFUNCTION(BlueprintCallable)
	TArray<int> GetPlayerPurses() const;

	UFUNCTION(BlueprintCallable)
	TArray<int> GetPlayerBalance() const;

	UFUNCTION(BlueprintCallable)
	void ResetPlayerBalance();
	

private:
	void BindUpdateMoney(URoguePurse* Purse, const int& PlayerIndex);

	UPROPERTY()
	TArray<int> PlayerPurses = {0,0,0,0};
	
	UPROPERTY()
	TArray<int> PlayerIndexes = {0,1,2,3};

	UPROPERTY()
	TArray<int> PlayerBalanceThisCycle = {0,0,0,0};
};
