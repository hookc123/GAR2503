// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/AIC_CodeAgentController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAIC_CodeAgentController::AAIC_CodeAgentController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_CodeAgentController::HandlePerception);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 900.0f;
	SightConfig->LoseSightRadius = 1100.0f;
	SightConfig->PeripheralVisionAngleDegrees = 40.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 600.0f;

	PerceptionComponent->ConfigureSense(*SightConfig);
}

void AAIC_CodeAgentController::BeginPlay()
{
	Super::BeginPlay();

	OnPossess(GetPawn());
}

void AAIC_CodeAgentController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
	if (UAIPerceptionSystem* PerceptionSystem = UAIPerceptionSystem::GetCurrent(GetWorld()))
	{
		PerceptionSystem->UpdateListener(*GetPerceptionComponent());
	}
}

void AAIC_CodeAgentController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// Get the possessed pawn
	if (IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(InPawn))
	{
		//Degugging
		UE_LOG(LogTemp, Warning, TEXT("Setting Team ID: %d"), TeamAgent->GetGenericTeamId());


		SetGenericTeamId(TeamAgent->GetGenericTeamId());
	}
	RunBehaviorTree(BehaviorTree);
}

void AAIC_CodeAgentController::HandlePerception(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsObject(PlayerName, Actor);
	}

}
