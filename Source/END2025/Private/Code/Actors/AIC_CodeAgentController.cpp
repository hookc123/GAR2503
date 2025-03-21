// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/AIC_CodeAgentController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAIC_CodeAgentController::AAIC_CodeAgentController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_CodeAgentController::HandlePerception);

	UAISenseConfig_Sight* SightConfig = NULL;
	SightConfig->SightRadius = 900.0f;
	SightConfig->LoseSightRadius = 1100.0f;
	SightConfig->PeripheralVisionAngleDegrees = 40.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

	PerceptionComponent->ConfigureSense(*SightConfig);
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
