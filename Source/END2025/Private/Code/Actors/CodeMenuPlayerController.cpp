// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeMenuPlayerController.h"
#include "Blueprint/UserWidget.h"

ACodeMenuPlayerController::ACodeMenuPlayerController()
{
    PrimaryActorTick.bCanEverTick = false;
    bShowMouseCursor = true;

}

void ACodeMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (MenuClass)
    {
        UUserWidget* MenuInstance = CreateWidget<UUserWidget>(this, MenuClass);
        if (MenuInstance)
        {
            MenuInstance->AddToViewport();

            // Setup Input Mode UI Only
            FInputModeUIOnly InputMode;
            InputMode.SetWidgetToFocus(MenuInstance->TakeWidget());
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

            SetInputMode(InputMode);
        }
    }
}