// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/CodeBasePickup.h"
#include "CodeDamagePickup.generated.h"


 class UParticleSystemComponent;
/**
 * 
 */
UCLASS()
class END2025_API ACodeDamagePickup : public ACodeBasePickup
{
	GENERATED_BODY()
	
public:

	ACodeDamagePickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UParticleSystemComponent* particleSystem;

protected:

	virtual void HandlePickup(AActor* otherActor, FHitResult hitResult) override;

	virtual void PostPickup() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float baseDamage;
private:

};
