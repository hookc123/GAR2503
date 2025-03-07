// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/AIC_CodeAgentController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


AAIC_CodeAgentController::AAIC_CodeAgentController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_CodeAgentController::HandlePerception);
}

void AAIC_CodeAgentController::BeginPlay()
{
	Super::BeginPlay();

	OnPossess(GetPawn());
}

void AAIC_CodeAgentController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// Get the possessed pawn

	RunBehaviorTree(BehaviorTree);
}

void AAIC_CodeAgentController::HandlePerception(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsObject(PlayerName, Actor);
	}
	else
	{
		Blackboard->ClearValue(PlayerName);
	}

}
