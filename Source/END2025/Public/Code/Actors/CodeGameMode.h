// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CodeGameMode.generated.h"

class UCodeResultsWidget;

/**
 * 
 */
UCLASS()
class END2025_API ACodeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACodeGameMode();

    UFUNCTION(BlueprintCallable)
    void AddEnemy(AActor* EnemyActor);

//protected:

    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UCodeResultsWidget> ResultsWidgetClass;

    UPROPERTY()
    UCodeResultsWidget* ResultsWidgetObj;

    UPROPERTY()
    int CurrentEnemyCount;

    UPROPERTY()
    class ABasePlayer* CurrentPlayer;

private:
    UPROPERTY(EditAnywhere)
    int NumberOfEnemies;

    UFUNCTION(BlueprintCallable)
    void RemoveEnemy(AActor* DestroyedActor);

    UFUNCTION(BlueprintCallable)
    void RemovePlayer();

};
