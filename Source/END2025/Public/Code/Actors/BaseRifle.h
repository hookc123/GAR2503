#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRifle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponActionDeleg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCallOnAmmoChanged, float, c, float, m);

UCLASS()
class END2025_API ABaseRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseRifle();

	//UFUNCTION(BlueprintCallable, Category = Weapon)
	void Attack();

	UFUNCTION(BlueprintPure, Category = Weapon)
	FVector GetSource();

	UFUNCTION(BlueprintCallable)
	void OwnerDied();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadAmmo();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void RequestReload();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ActionStopped();

	// Create a delegate
	UPROPERTY(BlueprintAssignable, Category = Delagate)
	FWeaponActionDeleg CallOnRifleAttack;

	UPROPERTY(BlueprintAssignable, Category = Delagate)
	FWeaponActionDeleg OnActionStopped;

	UPROPERTY(BlueprintAssignable, Category = Delagate)
	FCallOnAmmoChanged OnAmmoChanged;

	UPROPERTY(BlueprintAssignable, Category = Delagate)
	FWeaponActionDeleg OnReloadStart;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Defaults)
	class USkeletalMeshComponent* baseRifleMesh;

	// Parent Pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	APawn* ParentPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AActor> ProjectileClass;

	// Attack function

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FName WeaponSocketName;

	// Make custom event
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UseAmmo();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	float ResetTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	float maxAmmo;

private:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool CanShoot() const;
	bool ActionHappening;
	float currentAmmo;
	bool Alive = true;


};
