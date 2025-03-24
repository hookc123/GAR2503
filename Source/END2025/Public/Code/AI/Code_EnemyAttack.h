// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Code_EnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class END2025_API UCode_EnemyAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	//Contructor
	UCode_EnemyAttack();


protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

	void OnMessageReceived(UBehaviorTreeComponent& OwnerComp, const FAIMessage& Message);

	UPROPERTY(EditDefaultsOnly)
	FName FinishedMessage;

private:

	
};
