// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Utility/CodeGameInstance.h"

UCodeGameInstance::UCodeGameInstance() : FirstLevelIndex(1)
{
    GameLevels.Add(FName("CodeMainMenuMap"));
    GameLevels.Add(FName("CodeTestingMap"));
}

void UCodeGameInstance::LoadFirstLevel()
{
	LoadLevelSafe(FirstLevelIndex);
}

void UCodeGameInstance::QuitTheGame()
{
    FGenericPlatformMisc::RequestExit(false);
}

void UCodeGameInstance::LoadLevelSafe(int LevelIndex)
{

    if (!GameLevels.IsValidIndex(LevelIndex))
    {
        FString Error = FString::Printf(TEXT("ERROR: Level Index %d is not valid in the Game Instance"), LevelIndex);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Error);
        }
        return;
    }

    FName LevelName = GameLevels[LevelIndex];
    UWorld* World = GetWorld();

    if (World)
    {
        // ServerTravel works for both single and multiplayer games
        FString LevelString = LevelName.ToString();
        World->ServerTravel(LevelString);
    }
}
