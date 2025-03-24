#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"

// Delegate for health events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHurt, float, CurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, float, CurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeal, float, Ratio);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class END2025_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealth();

	// Handles when the actor takes damage
	UFUNCTION(BlueprintCallable)
	void HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Health variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHurt OnHurt;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHeal OnHeal;


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	float CurrentHealth;

};