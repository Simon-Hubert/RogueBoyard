#pragma once

#include "CoreMinimal.h"
#include "RogueLobby.h"
#include "RogueGrimoireLobby.generated.h"

class ARogueGrimoire;

UCLASS()
class ROGUEBOYARD_API ARogueGrimoireLobby : public ARogueLobby
{
	GENERATED_BODY()

public:
	ARogueGrimoireLobby();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginRoom() override;

	virtual void EndRoom() override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ARogueGrimoire* Grimoire;

};
