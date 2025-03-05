#include "Code/Utility/Health.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 5.0f;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	// Bind to damage events
	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealth::HandleDamage);
	}
}

void UHealth::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	// Apply damage as a reduction
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	// Fire OnHurt event with the ratio
	OnHurt.Broadcast(CurrentHealth / MaxHealth);

	// If health reaches 0, trigger death
	if (CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast(0.0);
	}
}

// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

