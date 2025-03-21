// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_CodeAgentController.generated.h"

/**
 * 
 */
UCLASS()
class END2025_API AAIC_CodeAgentController : public AAIController
{
	GENERATED_BODY()
	
public:

	AAIC_CodeAgentController();

	virtual void BeginPlay() override;

protected:

	UFUNCTION(BlueprintCallable, Category = AI)
	void OnPossess(APawn* InPawn) override;


	UPROPERTY(BlueprintReadOnly, Category = AI)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(BlueprintReadOnly, Category = AI)
	FName PlayerName;

private:
	UFUNCTION()
	void HandlePerception(AActor* Actor, FAIStimulus Stimulus);

};
