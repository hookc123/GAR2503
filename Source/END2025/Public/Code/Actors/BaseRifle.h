#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRifle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCallOnRifleAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCallOnActionStopped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCallOnAmmoChanged, float, c, float, m);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCallOnReloadStart);

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	float maxAmmo;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadAmmo();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void RequestReload();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ActionStopped();

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

	FTimerHandle timer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	float ResetTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create a delegate
	UPROPERTY(BlueprintAssignable, Category = Delagate)
	FCallOnRifleAttack CallOnRifleAttack;

	UPROPERTY(BlueprintAssignable, Category = Delagate)
	FCallOnActionStopped OnActionStopped;

	UPROPERTY(BlueprintAssignable, Category = Delagate)
	FCallOnAmmoChanged OnAmmoChanged;

	UPROPERTY(BlueprintAssignable, Category = Delagate)
	FCallOnReloadStart OnReloadStart;

	bool Alive = true;


private:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool CanShoot() const;
	bool ActionHappening;

	float currentAmmo;

	void HandleActionFinished();


};
