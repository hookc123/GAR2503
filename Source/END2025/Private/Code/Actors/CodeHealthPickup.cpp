// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeHealthPickup.h"
#include "Particles/ParticleSystemComponent.h"
#include "Code/Utility/CodePickupInterface.h"
#include "Components/BoxComponent.h"


ACodeHealthPickup::ACodeHealthPickup()
{
	baseDamage = -1.5f;

	particleSystem->SetRelativeLocation(FVector(0.f, 0.f, -40.f));

	particleSystem->SetRelativeScale3D(FVector(0.5f, 0.4f, 0.7f));

	boxCollision->SetRelativeScale3D(FVector(1.5f, 1.5f, 2.f));

}

void ACodeHealthPickup::PostPickup()
{
	ACodeBasePickup::PostPickup();
}

bool ACodeHealthPickup::CanPickup(AActor* otherActor)
{
	
	//Call can Pickup from the interface
	if (otherActor && otherActor->Implements<UCodePickupInterface>())
	{
		return ICodePickupInterface::Execute_CanPickupHealth(otherActor);
	}

	return false;
}
