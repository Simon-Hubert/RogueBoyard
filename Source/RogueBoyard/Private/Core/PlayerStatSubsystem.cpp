#include "Core/PlayerStatSubsystem.h"

#include "Characters/RogueCharacter.h"
#include "Economy/RoguePurse.h"

void UPlayerStatSubsystem::Init(TArray<ARogueCharacter*> Characters) {
	UE_LOG(LogTemp, Warning, TEXT("Stat Subsystem Init"));

	for(int i = 0; i<Characters.Num(); i++) {
		//URoguePurse* Purse = Cast<URoguePurse>(Characters[i]->K2_GetComponentsByClass(URoguePurse::StaticClass())[0]);
		URoguePurse* Purse = Characters[i]->Purse;
		if(Purse) {
			BindUpdateMoney(Purse, PlayerIndexes[i]);
		}
	}
}

TArray<int> UPlayerStatSubsystem::GetPlayerPurses() const {
	return PlayerPurses;
}

TArray<int> UPlayerStatSubsystem::GetPlayerBalance() const {
	return PlayerBalanceThisCycle;
}

void UPlayerStatSubsystem::ResetPlayerBalance() {
	PlayerBalanceThisCycle = {0, 0, 0, 0};
}

void UPlayerStatSubsystem::BindUpdateMoney(URoguePurse* Purse, const int& PlayerIndex) {
	auto OnMoneyUpdated = [&](int Amount)
	{
		PlayerBalanceThisCycle[PlayerIndex] += Amount - PlayerPurses[PlayerIndex] ;
		PlayerPurses[PlayerIndex] = Amount;
		//UE_LOG(LogTemp, Warning, TEXT("MyLambdaTest"));
	};
	Purse->OnUpdatedMoneyEvent.AddLambda(OnMoneyUpdated);
}

