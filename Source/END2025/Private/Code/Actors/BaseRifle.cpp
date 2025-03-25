// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseRifle.h"
#include "Code/Actors/Projectile.h"
#include <Code/Actors/BasePlayer.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ABaseRifle::ABaseRifle() : maxAmmo(5.0f)
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
	ReloadAmmo();
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

	if (CanShoot() && Alive)
	{
		ActionHappening = true;
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = controller;
		spawnParams.Instigator = ParentPawn;
		SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, pos, rotator, spawnParams);

		UE_LOG(LogTemp, Warning, TEXT("Successfully spawned projectile!"));

		// Define a delegate for the event
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("ActionStopped"));

		// Set a timer that calls ActionStopped using the delegate
		FTimerHandle timer;
		GetWorldTimerManager().SetTimer(timer, TimerDelegate, ResetTime, false);

		// Broadcast to the Delegate CallOnRifleAttack
		CallOnRifleAttack.Broadcast();
		UseAmmo();
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
	OnActionStopped.Broadcast();
}

void ABaseRifle::ReloadAmmo()
{
	UE_LOG(LogTemp, Warning, TEXT("Current Ammo: %f"), currentAmmo);
	UE_LOG(LogTemp, Warning, TEXT("Max Ammo: %f"), maxAmmo);

	currentAmmo = maxAmmo;
	OnAmmoChanged.Broadcast(currentAmmo, maxAmmo);
}

void ABaseRifle::RequestReload()
{
	if (!ActionHappening)
	{
		ActionHappening = true;
		OnReloadStart.Broadcast();
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Cannot Reload Now"));
	
}

void ABaseRifle::UseAmmo()
{
	if (currentAmmo <= 0)
		currentAmmo = 0.0f;
	else
		currentAmmo--;
	OnAmmoChanged.Broadcast(currentAmmo, maxAmmo);

	UE_LOG(LogTemp, Warning, TEXT("Current Ammo: %f"), currentAmmo);
}

bool ABaseRifle::CanShoot() const
{
	return !ActionHappening && Alive && currentAmmo > 0;
}


