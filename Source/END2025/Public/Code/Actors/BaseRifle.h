#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRifle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCallOnRifleAttack);

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
	void ActionStopped();

	FTimerHandle timer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	float ResetTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create a delegate
	UPROPERTY(BlueprintAssignable, Category = Delagate)
	FCallOnRifleAttack CallOnRifleAttack;

	bool Alive = true;


private:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool CanShoot() const;
	bool ActionHappening;

};
