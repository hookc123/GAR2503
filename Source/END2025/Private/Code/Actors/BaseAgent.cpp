// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseAgent.h"
#include "Code/Actors/BaseRifle.h"
#include "BrainComponent.h"
#include "Both/CharacterAnimation.h"
#include "BehaviorTree/BlackboardComponent.h"



ABaseAgent::ABaseAgent() : TintName("Tint"), ActionFinishedMessage("ActionFinished")
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseAgent::Attack()
{
	// Implementation of attack logic
	UE_LOG(LogTemp, Log, TEXT("ABaseAgent is attacking!"));
	if (WeaponObject)
	{
		WeaponObject->Attack();
	}
}

void ABaseAgent::Reload()
{
	if (WeaponObject)
	{
		WeaponObject->RequestReload();
	}
}

void ABaseAgent::BeginPlay()
{
	Super::BeginPlay();

	controller = Cast<AAIController>(GetController());

	if (!WeaponObject)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponObject is NULL for Agent: %s"), *GetName());
	}
	if (WeaponObject)
	{
		WeaponObject->OnActionStopped.AddDynamic(this, &ABaseAgent::HandleActionFinished);
	}
	UpdateBlackBoardHealth(1.0f);
	WeaponObject->OnAmmoChanged.AddDynamic(this, &ABaseAgent::UpdateBlackBoardAmmo);
	WeaponObject->ReloadAmmo();

	CharacterAnimation->OnDeathEnded.AddDynamic(this, &ABaseAgent::CallDestroy);
}

void ABaseAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WeaponObject)
	{
		//WeaponObject->Attack();
	}
}

void ABaseAgent::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (GetMesh())
	{
		USkeletalMeshComponent* DynamicMaterial = GetMesh();
		if (DynamicMaterial)
		{
			DynamicMaterial->SetVectorParameterValueOnMaterials(TintName, FVector(Color));
		}
	}
}

void ABaseAgent::HandleHurt(float ratio)
{
	Super::HandleHurt(ratio);
	UpdateBlackBoardHealth(ratio);
}

void ABaseAgent::HandleActionFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleActionFinished() called!"));
	FAIMessage message;
	message.MessageName = ActionFinishedMessage;
	message.Sender = this;
	message.Status = FAIMessage::Success;

	FAIMessage::Send(this, message);
}

void ABaseAgent::UpdateBlackBoardHealth(float ratio)
{

	UE_LOG(LogTemp, Log, TEXT("Updating Blackboard Health: %f"), ratio);

	if (controller)
	{
		UBlackboardComponent* Blackboard = controller->GetBlackboardComponent();
		if (Blackboard)
		{
			Blackboard->SetValueAsFloat("HealthRatio", ratio);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Blackboard is NULL for Agent: %s"), *GetName());
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Blackboard is NULL for Agent: %s"), *GetName());

}

void ABaseAgent::UpdateBlackBoardAmmo(float c, float m)
{
	if (controller)
	{
		UBlackboardComponent* Blackboard = controller->GetBlackboardComponent();
		if (Blackboard)
		{
			Blackboard->SetValueAsFloat("Ammo", c);
		}
	}

}

void ABaseAgent::CallDestroy()
{
	Destroy();
}
