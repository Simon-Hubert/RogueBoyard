// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuParentClass.generated.h"

UCLASS(Abstract)
class ROGUEBOYARD_API UMainMenuParentClass : public UUserWidget
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTransitionToMenu, int32, MenuIndex);

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FTransitionToMenu OnMenuTransition;

	UFUNCTION(BlueprintCallable, Category = "MenuActions")
	virtual void TransitionToMenu(int32 MenuIndex);
};
