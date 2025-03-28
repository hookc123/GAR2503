// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "Code/Actors/AIC_CodeAgentController.h"
#include "Code/Utility/CodeEnemyInterface.h"
#include "BaseAgent.generated.h"

/**
 * 
 */
UCLASS()
class END2025_API ABaseAgent : public ABaseCharacter, public ICodeEnemyInterface
{
	GENERATED_BODY()
	
public:

	ABaseAgent();
	virtual void Attack() override;
    virtual void Reload() override;

    virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }

protected:  

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void OnConstruction(const FTransform& Transform) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FName TintName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FLinearColor Color;

	virtual void HandleHurt(float ratio) override;
private:

	UFUNCTION()
	void HandleActionFinished();

    UFUNCTION()
    void UpdateBlackBoardHealth(float ratio);

    UFUNCTION()
    void UpdateBlackBoardAmmo(float c, float m);

    UFUNCTION()
    void CallDestroy();

	FName ActionFinishedMessage;

    AAIController* controller;
};
