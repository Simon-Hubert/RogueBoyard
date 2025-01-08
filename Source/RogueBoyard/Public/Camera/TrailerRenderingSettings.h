// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TrailerRenderingSettings.generated.h"

enum class ERenderTargetTexture : uint8;
/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName="Trailer Rendering Settings"))
class ROGUEBOYARD_API UTrailerRenderingSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	
	UPROPERTY(Config, EditAnywhere, Category="Rendering Settings")
	TArray<TSoftObjectPtr<UTextureRenderTarget2D>> RenderTargets;
	
};
