// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadNow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionEnded);

/**
 * 
 */
UCLASS()
class END2025_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
    //ctor
	UCharacterAnimation();

    UPROPERTY(BlueprintAssignable)
    FOnReloadNow OnReloadNow;

    UPROPERTY(BlueprintAssignable)
    FOnActionEnded OnActionEnded;

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void FireAnimation();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void HitAnimation(float notused = 0.0f);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void DeathAnimation();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void ReloadAnimation();

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
    FName ActionSlotName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Assets)
    UAnimSequenceBase* ReloadAsset;


    // Debugging variables
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Debugging)
    bool DebugFire;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Debugging)
    bool DebugHit;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Debugging)
    bool DebugDeath;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Debugging)
    bool DebugReload;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Defaults)
    float velocity;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Defaults)
    float direction;

    UFUNCTION(BlueprintNativeEvent)
    void PreviewWindowUpdate();

    virtual void PreviewWindowUpdate_Implementation();
};
