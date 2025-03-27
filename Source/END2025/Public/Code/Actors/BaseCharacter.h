// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Code/Utility/CodePickupInterface.h"	
#include "BaseCharacter.generated.h"

class UHealth;
//class UChildActorComponent;

UCLASS(Abstract)
class END2025_API ABaseCharacter : public ACharacter, public ICodePickupInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AActor> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ChildActorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class ABaseRifle* WeaponObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UCharacterAnimation* CharacterAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	UHealth* HealthComponent;

	UFUNCTION(BlueprintCallable)
	virtual void HandleHurt(float ratio);
	UFUNCTION(BlueprintCallable)
	virtual void HandleDeathStart(float ratio);

	virtual bool CanPickupHealth_Implementation() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnFirePressed();

	void OnReloadPressed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> baseCharacterMesh;
};
