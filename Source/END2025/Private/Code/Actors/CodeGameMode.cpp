// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeGameMode.h"
#include "Code/Actors/CodeMenuPlayerController.h"


ACodeGameMode::ACodeGameMode()
{
	PlayerControllerClass = ACodeMenuPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}
