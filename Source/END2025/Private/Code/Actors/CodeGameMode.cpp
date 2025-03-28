// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeGameMode.h"
#include "Code/Actors/BasePlayer.h"
#include "Code/Actors/CodeMenuPlayerController.h"
#include "Code/Widgets/CodeResultsWidget.h"
#include "EngineUtils.h"
#include "Code/Actors/CodeSpawner.h"


ACodeGameMode::ACodeGameMode() : NumberOfEnemies(0), CurrentEnemyCount(0), CurrentPlayer(nullptr)
{
	PlayerControllerClass = ACodeMenuPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}

void ACodeGameMode::BeginPlay()
{
    Super::BeginPlay();

    for (TActorIterator<ABaseCharacter> It(GetWorld()); It; ++It)
    {
		ABaseCharacter* Character = *It;
		if (Character)
		{
			if (Character->IsA<ABasePlayer>())
			{
				CurrentPlayer = Cast<ABasePlayer>(Character);
                CurrentPlayer->OnPlayerLost.AddDynamic(this, &ACodeGameMode::RemovePlayer);
            }
			else
			{
				AddEnemy(Character);
			}
		}
    }

	for (TActorIterator<ACodeSpawner> It(GetWorld()); It; ++It)
	{
		ACodeSpawner* Spawner = *It;
		if (Spawner)
		{
            AddEnemy(Spawner);
		}
	}

    // Create UI Widget
    if (ResultsWidgetClass)
    {
		UE_LOG(LogTemp, Warning, TEXT("ResultsWidgetClass is not NULL!"));
        ResultsWidgetObj = CreateWidget<UCodeResultsWidget>(GetWorld(), ResultsWidgetClass);
    }
    else
	{
		UE_LOG(LogTemp, Error, TEXT("ResultsWidgetClass is NULL!"));
	}
}

void ACodeGameMode::AddEnemy(AActor* EnemyActor)
{
    if (EnemyActor)
    {
        EnemyActor->OnDestroyed.AddDynamic(this, &ACodeGameMode::RemoveEnemy);
        NumberOfEnemies++;
        GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("Enemies: %d"), NumberOfEnemies));
    }
	else if (!EnemyActor)
    {
        UE_LOG(LogTemp, Error, TEXT("EnemyActor is NULL!"));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EnemyActor is NULL!"));
    }
}

void ACodeGameMode::RemoveEnemy(AActor* DestroyedActor)
{
    NumberOfEnemies--;
    GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("ENEMY DESTROYED! Enemies Left: %d"), NumberOfEnemies));
    if (NumberOfEnemies <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("YOU WIN!"));
        GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Yellow, TEXT("YOU WIN!"));
        if (ResultsWidgetObj)
        {
            ResultsWidgetObj->AddToViewport();
			ResultsWidgetObj->SetWin();
        }
        if (CurrentPlayer)
        {
            CurrentPlayer->PlayerWin();
        }
    }
}

void ACodeGameMode::RemovePlayer()
{
    GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("YOU LOSE!"));

    if (ResultsWidgetObj)
    {
        // Show widget on screen
        ResultsWidgetObj->AddToViewport();


        if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
        {
            // Switch to UI-only input
            FInputModeUIOnly InputMode;
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            InputMode.SetWidgetToFocus(ResultsWidgetObj->TakeWidget());

            PC->SetInputMode(InputMode);
            PC->bShowMouseCursor = true;
        }
    }

    // Null out player reference (if needed)
    CurrentPlayer = nullptr;
}
