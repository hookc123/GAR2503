// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseAgent.h"
#include "Code/Actors/BaseRifle.h"

ABaseAgent::ABaseAgent()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseAgent::BeginPlay()
{
    Super::BeginPlay();

    if (!WeaponObject)
    {
        UE_LOG(LogTemp, Error, TEXT("WeaponObject is NULL for Agent: %s"), *GetName());
    }
}


void ABaseAgent::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (WeaponObject)
    {
        WeaponObject->Attack();
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