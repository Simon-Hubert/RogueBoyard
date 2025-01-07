// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrailerRenderingSettings.h"
#include "Subsystems/WorldSubsystem.h"
#include "CameraTrailerWorldSubsystem.generated.h"
/**
 * 
 */
UCLASS()
class ROGUEBOYARD_API UCameraTrailerWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void AddCamera(USceneCaptureComponent2D* Camera);
	virtual void PostInitialize() override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override {return TStatId(); };
private:
	TArray<UTextureRenderTarget2D*> RenderTargets;
	TMap<UTextureRenderTarget2D*, USceneCaptureComponent2D*> RenderTargetTextureMap;

	int Frame = 0;
};
