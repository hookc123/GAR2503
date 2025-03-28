// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "Both/PlayerHUD.h"
#include "BasePlayer.generated.h"

//OnplayerLostDelegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDeleg);


/**
 * 
 */
UCLASS()
class END2025_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABasePlayer();

	UUserWidget* GetHUDWidget() { return HUDWidget; }

	UPROPERTY(BlueprintAssignable)
	FPlayerDeleg OnPlayerLost;

	UFUNCTION()
	void PlayerWin();

	virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }

protected:

	virtual void BeginPlay() override;

	//virtual void Attack(FRotator rotator) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);// override;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UPlayerHUD> HUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	APlayerController* PlayerController;

	void HandleHurt(float ratio) override;

	void HandleDeathStart(float ratio) override;

	virtual bool CanPickupHealth_Implementation() override;
	virtual bool CanPickupAmmo_Implementation() override;


private:
	UPROPERTY()
	UUserWidget* HUDWidget;

	void InputAxisMoveForward(float AxisValue);

	void InputAxisStrafe(float AxisValue);
	UFUNCTION()
	void PlayerLost();

};
