// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MainMenuCameraView.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"


// Sets default values
AMainMenuCameraView::AMainMenuCameraView()
{
	// Caméra component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);

	// Widget component
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
    
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainMenuCameraView::BeginPlay()
{
	Super::BeginPlay();
    
}

// Called every frame
void AMainMenuCameraView::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
