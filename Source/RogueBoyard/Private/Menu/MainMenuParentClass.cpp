// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MainMenuParentClass.h"

void UMainMenuParentClass::TransitionToMenu(int32 MenuIndex)
{
	//event dispatcher
	OnMenuTransition.Broadcast(MenuIndex);
	UE_LOG(LogTemp, Warning, TEXT("Event triggered with menu index: %d"), MenuIndex);
}
