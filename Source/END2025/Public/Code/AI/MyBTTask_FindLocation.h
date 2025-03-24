// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_FindLocation.generated.h"

/**
 * 
 */
UCLASS()

class END2025_API UMyBTTask_FindLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	//Contructor
	UMyBTTask_FindLocation();


protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

private:

	UPROPERTY(EditDefaultsOnly)
	float Radius;

	UPROPERTY(EditDefaultsOnly)
	FName LocationName;

};
