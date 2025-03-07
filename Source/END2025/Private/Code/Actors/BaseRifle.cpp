// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseRifle.h"
#include "Code/Actors/Projectile.h"
#include <Code/Actors/BasePlayer.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ABaseRifle::ABaseRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Set the skeletal mesh as the root component
	baseRifleMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BaseRifleMesh");
	SetRootComponent(baseRifleMesh);

	// Set the projectile class
	ProjectileClass = AProjectile::StaticClass();
}

// Called when the game starts or when spawned
void ABaseRifle::BeginPlay()
{
	Super::BeginPlay();
	ParentPawn = Cast<APawn>(GetParentActor());
	if (ParentPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Parent Pawn: %s"), *ParentPawn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Owner Must be A Pawn"));
		Destroy();
	}
}

void ABaseRifle::Attack()
{
	AProjectile* SpawnedProjectile = nullptr;

	FVector pos;
	FRotator rotator;

	ABasePlayer* Player = Cast<ABasePlayer>(ParentPawn);
	if (Player)
	{
		auto hudWidget = Player->GetHUDWidget();
		// Player-specific logic for setting rotation
		if (!hudWidget) return;

		UPlayerHUD* PlayerHUD = Cast<UPlayerHUD>(hudWidget);
		if (!PlayerHUD) return;

		FVector StartLocation = GetSource();  // Get rifle's firing position
		FVector EndLocation = PlayerHUD->GetDestination(); // Get crosshair destination

		// Calculate rotation from weapon to crosshair target
		rotator = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);
	}
	else
	{
		rotator = ParentPawn->GetBaseAimRotation();
	}	auto controller = ParentPawn->GetController();
	
	pos = GetSource();

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = controller;
	spawnParams.Instigator = ParentPawn;

	if(CanShoot()&& Alive)
	SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, pos, rotator, spawnParams);

	if (SpawnedProjectile)
	{
		ActionHappening = true;
		UE_LOG(LogTemp, Warning, TEXT("Successfully spawned projectile!"));

		// Define a delegate for the event
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("ActionStopped"));

		// Set a timer that calls ActionStopped using the delegate
		GetWorldTimerManager().SetTimer(timer, TimerDelegate, ResetTime, false);

		// Broadcast to the Delegate CallOnRifleAttack
		CallOnRifleAttack.Broadcast();

	}	
}

FVector ABaseRifle::GetSource()
{
	return baseRifleMesh->GetSocketLocation(WeaponSocketName);
}

void ABaseRifle::OwnerDied()
{
	Alive = false;
}

void ABaseRifle::ActionStopped()
{
	ActionHappening = false;
}

// Called every frame
void ABaseRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseRifle::CanShoot() const
{
	return !ActionHappening;
}

void ABaseRifle::HandleActionFinished()
{
	OnActionStopped.Broadcast();
}

