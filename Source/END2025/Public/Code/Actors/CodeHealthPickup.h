// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/CodeDamagePickup.h"
#include "CodeHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class END2025_API ACodeHealthPickup : public ACodeDamagePickup
{
	GENERATED_BODY()
	
public:
	ACodeHealthPickup();

protected:

	virtual void PostPickup() override;

	virtual bool CanPickup(AActor* otherActor) override;

private:

};
