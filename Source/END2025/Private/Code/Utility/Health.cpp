#include "Code/Utility/Health.h"

// Sets default values for this component's properties
UHealth::UHealth() : MaxHealth(5.0f), CurrentHealth(MaxHealth)
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	// Bind to damage events
	AActor* Owner = GetOwner();
	if (Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Binding %s to OnTakeAnyDamage"), *Owner->GetName());
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealth::HandleDamage);
	}
}

void UHealth::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0.0f)
	{
		return;
	}

	// Apply damage as a reduction
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	// Fire OnHurt event with the ratio
	if (Damage > 0.0f)
	{
		// Took damage
		OnHurt.Broadcast(CurrentHealth/MaxHealth);

		//Debug Log health and Actor name
		FString message = FString::Printf(
			TEXT("Actor: %s has %.1f health remaining"),
			*DamagedActor->GetName(),
			CurrentHealth
		);

		UE_LOG(LogTemp, Warning, TEXT("%s"), *message);

		if (GEngine && DamagedActor)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.0f,
				FColor::Red,
				message
			);
		}
		///////////////////////////
		if (CurrentHealth <= 0.0f)
		{
			OnDeath.Broadcast(0.0f);
		}
	}
	else
	{
		// Healed
		OnHeal.Broadcast(CurrentHealth / MaxHealth);
	}
}

// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

