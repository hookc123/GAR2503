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

void UCharacterAnimation::FireAnimation()
{
	if (FireAsset)
	{
		PlaySlotAnimationAsDynamicMontage(FireAsset, ActionSlotName);
	}
}

void UCharacterAnimation::HitAnimation(float notUsed)
{
	if (HitAsset)
	{
		PlaySlotAnimationAsDynamicMontage(HitAsset, ActionSlotName);
	}
}

void UCharacterAnimation::DeathAnimation()
{
	CurrentDeathAsset = DeathAssets[ FMath::Rand() % (DeathAssets.Num() - 1) ];
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
}
