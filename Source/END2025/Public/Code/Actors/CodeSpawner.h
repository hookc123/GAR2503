// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseAgent.h"
#include "CodeSpawner.generated.h"


/**
 * 
 */
UCLASS()
class END2025_API ACodeSpawner : public AActor
{
	GENERATED_BODY()
public:

	ACodeSpawner();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Defaults)
	class UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseAgent> AgentToSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	class UHealth* HealthComponent;

	UFUNCTION()
	void OnSpawnerDeath(float ratio);

private:

	void SpawnAgent();

};
