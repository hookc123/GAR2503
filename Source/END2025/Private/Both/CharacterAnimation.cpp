// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CharacterAnimation.h"
#include "KismetAnimationLibrary.h"

void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* pawn = TryGetPawnOwner();
	if (pawn)
	{
		// Is Valid
		FVector returnValue = pawn->GetVelocity();
		velocity = returnValue.Size();
		direction = UKismetAnimationLibrary::CalculateDirection(pawn->GetVelocity(), pawn->GetActorRotation());
	}
		// Not Valid
		PreviewWindowUpdate();
}

UCharacterAnimation::UCharacterAnimation() : velocity(0.0f), 
direction(0.0f), 
DebugFire(false), 
DebugHit(false), 
DebugDeath(false), 
CurrentDeathAsset(nullptr), 
ActionSlotName("Action")
{}

void UCharacterAnimation::FireAnimation_Implementation()
{
	if (FireAsset)
	{
		PlaySlotAnimationAsDynamicMontage(FireAsset, ActionSlotName);
	}
}

void UCharacterAnimation::PlayFireAnimation()
{
	FireAnimation();
}

void UCharacterAnimation::HitAnimation_Implementation(float notused)
{
	if (HitAsset)
	{
		PlaySlotAnimationAsDynamicMontage(HitAsset, ActionSlotName);
	}

}

void UCharacterAnimation::PlayHitAnimation(float Ratio, bool NotUsed)
{
	HitAnimation(Ratio);
}

void UCharacterAnimation::DeathAnimation_Implementation()
{
	if (DeathAssets.Num() > 0)
	{
		CurrentDeathAsset = DeathAssets[FMath::RandRange(0, DeathAssets.Num() - 1)];
		PlaySlotAnimationAsDynamicMontage(CurrentDeathAsset, ActionSlotName);
	}
}

void UCharacterAnimation::PlayDeathAnimation()
{
	DeathAnimation();
}

void UCharacterAnimation::ReloadAnimation_Implementation()
{
	if (ReloadAsset)
	{
		PlaySlotAnimationAsDynamicMontage(ReloadAsset, ActionSlotName);
	}
}

void UCharacterAnimation::PlayReloadAnimation()
{
	ReloadAnimation();
}


void UCharacterAnimation::PreviewWindowUpdate_Implementation()
{
	if (DebugFire)
	{
		DebugFire = false;
		FireAnimation();
	}

	if (DebugHit)
	{
		DebugHit = false;
		HitAnimation();
	}

	if (DebugDeath)
	{
		DebugDeath = false;
		DeathAnimation();
	}
	if (DebugReload)
	{
		DebugReload = false;
		ReloadAnimation();
	}
}
