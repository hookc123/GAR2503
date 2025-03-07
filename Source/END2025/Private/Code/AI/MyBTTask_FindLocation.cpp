// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/AI/MyBTTask_FindLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UMyBTTask_FindLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) {
		UE_LOG(LogTemp, Error, TEXT("We need a Valid Controller"));
		return EBTNodeResult::Failed;
	}
	APawn* pawn = controller->GetPawn();
	if (!pawn) {
		UE_LOG(LogTemp, Error, TEXT("We need a Valid Pawn"));

		return EBTNodeResult::Failed;
	}
	UNavigationSystemV1* navi = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!navi) {
		UE_LOG(LogTemp, Error, TEXT("We need a Valid Navigation System"));
		return EBTNodeResult::Failed;
	}
	FVector origin = pawn->GetActorLocation();

	FVector randLocation;
	FNavLocation naviLocation;

	if (navi->GetRandomPointInNavigableRadius(origin, Radius, naviLocation))
		randLocation = naviLocation;
	else {
		UE_LOG(LogTemp, Error, TEXT("Get Random Point In NavigableRadius FAILED"));
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* bBoard = controller->GetBlackboardComponent();
	if (bBoard)
		bBoard->SetValueAsVector(LocationName, randLocation);

	return EBTNodeResult::Succeeded;
}
