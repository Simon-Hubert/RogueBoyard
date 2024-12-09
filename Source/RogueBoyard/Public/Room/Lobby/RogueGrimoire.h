#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueGrimoire.generated.h"

class ARogueCharacter;

UCLASS()
class ROGUEBOYARD_API ARogueGrimoire : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGrimoireChangedOwner);

public:
	ARogueGrimoire();
	virtual void Tick(float DeltaTime) override;
	ARogueCharacter* GetCurrentOwner() const;

	UPROPERTY(BlueprintAssignable)
	FOnGrimoireChangedOwner OnGrimoireChangedOwnerEvent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ARogueCharacter* CurrentOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ARogueCharacter* LastOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bGrounded = true;

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Init"))
	void ReceiveInit();
	FVector LastInputPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FVector DefaultPos;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SwitchOwner(ARogueCharacter* NewOwner);

private:
	
	UPROPERTY(EditAnywhere)
	float F;

	UPROPERTY(EditAnywhere)
	float Zeta;

	UPROPERTY(EditAnywhere)
	float R;

	FVector Velocity;

	
	float K1, K2, K3;
	void ComputeConstants();
};
