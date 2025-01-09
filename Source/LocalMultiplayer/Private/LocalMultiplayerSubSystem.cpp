// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalMultiplayerSubSystem.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
//#include "K2Node_GetSubsystem.h"
#include "LocalMultiplayerSettings.h"
#include "Kismet/GameplayStatics.h"

void ULocalMultiplayerSubSystem::ResetAllPlayers()
{
	UWorld* World = GetWorld();
	if(!World) return;

	const int Players = GEngine->GetNumGamePlayers(World);
	for(int i = Players - 1; i >= 0; i--)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(World, i);
		if(PC) UGameplayStatics::RemovePlayer(PC, true);
	}

	PlayerIndexFromGamepadProfileIndex.Empty();
	PlayerIndexFromKeyboardProfileIndex.Empty();

	LastAssignedPlayerIndex = -1;
	const int Players2 = GEngine->GetNumGamePlayers(World);
	UE_LOG(LogTemp, Display, TEXT("Players: %d"), Players2);
	OnAllPlayersReset.Broadcast();
}

void ULocalMultiplayerSubSystem::CreateAndInitPlayers(ELocalMultiplayerInputMappingType MappingType)
{
	int nKbProfile = GetDefault<ULocalMultiplayerSettings>()->GetNbKeyboardProfiles();
	for(int i = 1; i < nKbProfile + GetDefault<ULocalMultiplayerSettings>()->NbMaxGamepads; i++)
	{
		UGameplayStatics::CreatePlayer(GetWorld(), i);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(
		//TEXT("PlayerIndex: %i"),
		//i));
	}
	for (auto Element : PlayerIndexFromKeyboardProfileIndex)
	{
		AssignKeyboardMapping(Element.Value, Element.Key, MappingType);
	}
	for (auto Element : PlayerIndexFromGamepadProfileIndex)
	{
		AssignGamepadInputMapping(Element.Value, MappingType);
	}
}

int ULocalMultiplayerSubSystem::GetAssignedPlayerIndexFromKeyboardProfileIndex(int KeyboardProfileIndex)
{
	if(PlayerIndexFromKeyboardProfileIndex.Contains(KeyboardProfileIndex)) return PlayerIndexFromKeyboardProfileIndex[KeyboardProfileIndex];
	return -1;
}

int ULocalMultiplayerSubSystem::AssignNewPlayerToKeyboardProfile(int KeyboardProfileIndex)
{
	LastAssignedPlayerIndex++;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
	//	"lol" + FString::SanitizeFloat(LastAssignedPlayerIndex));
	PlayerIndexFromKeyboardProfileIndex.Add(KeyboardProfileIndex, LastAssignedPlayerIndex);
	
	OnNewPlayerJoinedEvent.Broadcast(LastAssignedPlayerIndex);
	if(LastAssignedPlayerIndex == 3) OnAllPlayersJoined.Broadcast(); 
	return LastAssignedPlayerIndex;
}

void ULocalMultiplayerSubSystem::AssignKeyboardMapping(int PlayerIndex, int KeyboardProfileIndex,
	ELocalMultiplayerInputMappingType MappingType) const
{
	ULocalPlayer* Player = UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex)->GetLocalPlayer();
	if(!Player) return;
		Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()
		->AddMappingContext(GetDefault<ULocalMultiplayerSettings>()
		->KeyBoardProfilesData[KeyboardProfileIndex].GetIMCFromType(MappingType), 1);
	//GEngine->AddOnScreenDebugMessage(
	//-1,
	//3.f,
	//FColor::Cyan,
	//("AssignKeyboard" +  KeyboardProfileIndex)
	//);
	//GEngine->AddOnScreenDebugMessage(
	//-1,
	//3.f,
	//FColor::Cyan,
	//("ToPlayer" + PlayerIndex)
	//);
}

int ULocalMultiplayerSubSystem::GetAssignedPlayerIndexFromGamepadDeviceID(int DeviceID)
{
	if(PlayerIndexFromGamepadProfileIndex.Contains(DeviceID))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(
		//TEXT("Device ID: %i"),
		//DeviceID));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(
		//	TEXT("PlayerIndex: %i"),
		//	*PlayerIndexFromGamepadProfileIndex.Find(DeviceID)));
		return *PlayerIndexFromGamepadProfileIndex.Find(DeviceID);
	}
	return -1;
}

int ULocalMultiplayerSubSystem::AssignNewPlayerToGamepadDeviceID(int DeviceID)
{
	LastAssignedPlayerIndex++;
	//GEngine->AddOnScreenDebugMessage(
	//-1,
	//15.0f,
	//FColor::Yellow,
	//FString::Printf(TEXT("Index: %i"),LastAssignedPlayerIndex));
	PlayerIndexFromGamepadProfileIndex.Add(DeviceID, LastAssignedPlayerIndex);
	OnNewPlayerJoinedEvent.Broadcast(LastAssignedPlayerIndex);
	if(LastAssignedPlayerIndex == 3) OnAllPlayersJoined.Broadcast(); 
	return LastAssignedPlayerIndex;
}

void ULocalMultiplayerSubSystem::AssignGamepadInputMapping(int PlayerIndex,
	ELocalMultiplayerInputMappingType MappingType) const
{
	ULocalPlayer* Player = UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex)->GetLocalPlayer();
	if(!Player) return;
	Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()
	->AddMappingContext(GetDefault<ULocalMultiplayerSettings>()
	->GamepadProfilData.GetIMCFromType(MappingType), 1);
	//GEngine->AddOnScreenDebugMessage(
	//-1,
	//3.f,
	//FColor::Cyan,
	//("ToPlayer" + PlayerIndex));
}
