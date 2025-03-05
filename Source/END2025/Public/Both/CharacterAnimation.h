// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"

/**
 * 
 */
UCLASS()
class END2025_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
    UFUNCTION(BlueprintCallable, Category = "Animation")
    void FireAnimation();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void HitAnimation(float notused = 0.0f);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void DeathAnimation();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Assets)
    UAnimSequenceBase* FireAsset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Assets)
    UAnimSequenceBase* HitAsset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Assets)
    UAnimSequenceBase* DeathAsset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Assets)
    UAnimSequenceBase* CurrentDeathAsset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Assets)
    TArray<UAnimSequenceBase*> DeathAssets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Defaults)
    FName ActionSlotName = "Action";

    // Debugging variables
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Debugging)
    bool DebugFire = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Debugging)
    bool DebugHit = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Debugging)
    bool DebugDeath = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Defaults)
    float velocity = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Defaults)
    float direction = 0.0f;

    UFUNCTION(BlueprintNativeEvent)
    void PreviewWindowUpdate();

    virtual void PreviewWindowUpdate_Implementation();
};
