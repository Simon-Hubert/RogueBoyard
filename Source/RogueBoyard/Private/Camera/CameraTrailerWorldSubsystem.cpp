// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraTrailerWorldSubsystem.h"

#include "ImageUtils.h"
#include "Components/SceneCaptureComponent2D.h"

#include  "Engine/TextureRenderTarget2D.h"
#include "Exporters/TextureExporterPNG.h"
#include "Serialization/BufferArchive.h"

void UCameraTrailerWorldSubsystem::AddCamera(USceneCaptureComponent2D* Camera)
{
	if(RenderTargetTextureMap.FindKey(Camera)) return;
	
	for (UTextureRenderTarget2D* Element : RenderTargets)
	{
		if(!RenderTargetTextureMap.Contains(Element))
		{
			RenderTargetTextureMap.Add(Element, Camera);
			Camera->TextureTarget = Element;
			break;
		}
	}
}

void UCameraTrailerWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
	const UTrailerRenderingSettings* Settings = GetDefault<UTrailerRenderingSettings>();
	for (int i = 0; i < Settings->RenderTargets.Num(); i++)
	{
		UTextureRenderTarget2D* RenderTarget = Settings->RenderTargets[i].LoadSynchronous();
		RenderTargets.Add(RenderTarget);
	}
}

void UCameraTrailerWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Frame++;
	for (auto Element : RenderTargetTextureMap)
	{
		FString ThumbnailFile = "C:/Users/Enzo/Desktop/RogueBoyard/Trailer/" + Element.Value->GetOwner()->GetName() + "/" + FString::FromInt(Frame) + ".png";
		FArchive* Ar = IFileManager::Get().CreateFileWriter(*ThumbnailFile);
		FBufferArchive Buffer;
		
		bool bSuccess = FImageUtils::ExportRenderTarget2DAsPNG(Element.Key, Buffer);
		if (bSuccess)
		{
			Ar->Serialize(const_cast<uint8*>(Buffer.GetData()), Buffer.Num());
		}

		delete Ar;
	}
}
