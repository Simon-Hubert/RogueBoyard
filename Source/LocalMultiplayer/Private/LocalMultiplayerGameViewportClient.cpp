// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerGameViewportClient.h"

#include "LocalMultiplayerSettings.h"
#include "LocalMultiplayerSubSystem.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"

void ULocalMultiplayerGameViewportClient::PostInitProperties()
{
	Super::PostInitProperties();
	MaxSplitscreenPlayers = 8;
}

bool ULocalMultiplayerGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	ULocalMultiplayerSubSystem* Multiplayer = GameInstance->GetSubsystem<ULocalMultiplayerSubSystem>();
    const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
    int PlayerIndex = -1;
    
    if(EventArgs.IsGamepad())
    {
        GEngine->AddOnScreenDebugMessage(1,5.0f, FColor::Red, "GamepadInput");
        if(Multiplayer->GetAssignedPlayerIndexFromGamepadDeviceID(EventArgs.InputDevice.GetId()) < 0)
        {
        	if(Multiplayer->bIsInMenuSelection)
        	{
        		PlayerIndex = Multiplayer->AssignNewPlayerToGamepadDeviceID(EventArgs.InputDevice.GetId());
        		Multiplayer->AssignGamepadInputMapping(
					PlayerIndex,
					ELocalMultiplayerInputMappingType::InGame);
        	}
        }
        else
        {
            PlayerIndex = Multiplayer->GetAssignedPlayerIndexFromGamepadDeviceID(EventArgs.InputDevice.GetId());
        }
    }
    else
    {
        int KeyboardProfileIndex = Settings->FindKeyboardProfileFromKey(EventArgs.Key, ELocalMultiplayerInputMappingType::InGame);
        if(KeyboardProfileIndex < 0)
        {
            //GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, "Key not assigned");
        } else if (Multiplayer->GetAssignedPlayerIndexFromKeyboardProfileIndex(KeyboardProfileIndex) < 0)
        {
        	if(Multiplayer->bIsInMenuSelection)
        	{
        		PlayerIndex = Multiplayer->AssignNewPlayerToKeyboardProfile(KeyboardProfileIndex);
        		Multiplayer->AssignKeyboardMapping(
					PlayerIndex,
					KeyboardProfileIndex,
					ELocalMultiplayerInputMappingType::InGame);
        	}
        }
        else
        {
            PlayerIndex = Multiplayer->GetAssignedPlayerIndexFromKeyboardProfileIndex(KeyboardProfileIndex);
        }
    }

    if(PlayerIndex >= 0)
    {
        FInputKeyParams inputArgs(EventArgs.Key, EventArgs.Event, static_cast<double>(EventArgs.AmountDepressed), EventArgs.IsGamepad());
        return UGameplayStatics::GetPlayerController(GetGameInstance()->GetWorld(), PlayerIndex)->InputKey(inputArgs);
    }
    return Super::InputKey(EventArgs);
}

bool ULocalMultiplayerGameViewportClient::InputAxis(FViewport* InViewPort, FInputDeviceId InputDevice, FKey Key,
	float Delta, float Deltatime, int32 NumSamples, bool bGamepad)
{
	ULocalMultiplayerSubSystem* Multiplayer = GameInstance->GetSubsystem<ULocalMultiplayerSubSystem>();
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();

	int PlayerIndex = -1;
	if(bGamepad)
	{
		//GEngine->AddOnScreenDebugMessage(1,5.0f, FColor::Red, "GamepadAxis");

		if(Multiplayer->GetAssignedPlayerIndexFromGamepadDeviceID(InputDevice.GetId()) < 0)
		{
			if(Multiplayer->bIsInMenuSelection)
			{
				PlayerIndex = Multiplayer->AssignNewPlayerToGamepadDeviceID(InputDevice.GetId());
				Multiplayer->AssignGamepadInputMapping(
					PlayerIndex,
					ELocalMultiplayerInputMappingType::InGame);
			}
		}
		else
		{
			PlayerIndex = Multiplayer->GetAssignedPlayerIndexFromGamepadDeviceID(InputDevice.GetId());
		}
	}
	else
	{
		int KeyboardProfileIndex = Settings->FindKeyboardProfileFromKey(Key, ELocalMultiplayerInputMappingType::InGame);
		if(KeyboardProfileIndex < 0)
		{
			//GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, "Key not assigned");
		} else if (Multiplayer->GetAssignedPlayerIndexFromKeyboardProfileIndex(KeyboardProfileIndex) < 0)
		{
		if(Multiplayer->bIsInMenuSelection)
		{
			PlayerIndex = Multiplayer->AssignNewPlayerToKeyboardProfile(KeyboardProfileIndex);
			Multiplayer->AssignKeyboardMapping(
				PlayerIndex,
				KeyboardProfileIndex,
				ELocalMultiplayerInputMappingType::InGame);
		}

		}
		else
		{
			PlayerIndex = Multiplayer->GetAssignedPlayerIndexFromKeyboardProfileIndex(KeyboardProfileIndex);
		}
	}
    
	if(PlayerIndex >= 0)
	{
		return UGameplayStatics::GetPlayerController(GetGameInstance()->GetWorld(), PlayerIndex)->InputAxis(Key, Delta, Deltatime, NumSamples, bGamepad);
	}
	return Super::InputAxis(Viewport, InputDevice, Key, Delta, Deltatime, NumSamples, bGamepad);
}
