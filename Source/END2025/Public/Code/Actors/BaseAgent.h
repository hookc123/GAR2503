// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "BaseAgent.generated.h"

/**
 * 
 */
UCLASS()
class END2025_API ABaseAgent : public ABaseCharacter
{
	GENERATED_BODY()
	
public:

	ABaseAgent();

protected:  

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void OnConstruction(const FTransform& Transform) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FName TintName = "Tint";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FLinearColor Color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    class UCharacterAnimation* AnimationBP;

private:

};
