// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodePlayerController.h"

ACodePlayerController::ACodePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACodePlayerController::BeginPlay()
{
	Super::BeginPlay();

    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);

}
