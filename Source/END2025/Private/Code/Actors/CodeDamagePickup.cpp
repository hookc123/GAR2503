// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeDamagePickup.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"


ACodeDamagePickup::ACodeDamagePickup() : baseDamage(2.f)
{
	particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));

	particleSystem->SetRelativeLocation(FVector(0.f, 0.f, -30.f));

	particleSystem->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.25f));

	particleSystem->SetupAttachment(RootComponent);
	boxCollision->SetRelativeScale3D(FVector(1.6f, 1.6f, 1.6f));
}

void ACodeDamagePickup::HandlePickup(AActor* otherActor, FHitResult hitResult)
{
	Super::HandlePickup(otherActor, hitResult);

	FDamageEvent DamageEvent;

	// Call TakeDamage directly on the OtherActor
	otherActor->TakeDamage(baseDamage, DamageEvent, Cast<AController>(GetOwner()), this);


	UE_LOG(LogTemp, Warning, TEXT("Damage Applied: %f"), baseDamage);
}

void ACodeDamagePickup::PostPickup()
{}
