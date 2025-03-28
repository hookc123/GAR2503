// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Code/Actors/BaseRifle.h"
#include <Kismet/KismetMathLibrary.h>
#include "Code/Utility/Health.h"
#include "Both/CharacterAnimation.h"

ABasePlayer::ABasePlayer()
{
	// Create a SpringArmComponent
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetRelativeLocation(FVector(0., 0., 60.));
	SpringArm->SetupAttachment(GetRootComponent()/*, only need to use this if we are using sockets*/);
	// Create a CameraComponent
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Get Player Controller
	PlayerController = Cast<APlayerController>(GetController());

	// Ensure PlayerController exists
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("We Need A Player Controller to spawn the HUD"));
		return;
	}
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("We Need A Health Component to spawn the HUD"));
	}

	// Create and add HUD to viewport
	if (HUDClass)
	{
		HUDWidget = CreateWidget(PlayerController, HUDClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
		if (HUDWidget)
		{
			UPlayerHUD* PlayerHUD = Cast<UPlayerHUD>(HUDWidget);
			if (PlayerHUD)
			{
				HealthComponent->OnHurt.AddDynamic(PlayerHUD, &UPlayerHUD::SetHealth);
				HealthComponent->OnDeath.AddDynamic(PlayerHUD, &UPlayerHUD::SetHealth);
				WeaponObject->OnAmmoChanged.AddDynamic(PlayerHUD, &UPlayerHUD::SetAmmo);
				WeaponObject->ReloadAmmo();
				HealthComponent->OnHeal.AddDynamic(PlayerHUD, &UPlayerHUD::SetHealth);
				CharacterAnimation->OnDeathEnded.AddDynamic(this, &ABasePlayer::PlayerLost);
			}

			if (HUDClass)
			{
				UE_LOG(LogTemp, Warning, TEXT("HUDClass is valid: %s"), *HUDClass->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("HUDClass is NULL at runtime!"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HUDClass is NULL at runtime!"));
	}

}


void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Do not forget to call parent function
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Bind the axis inputs

	// Use Pawn Control Rotation in the spring arm
	SpringArm->bUsePawnControlRotation = true;
	PlayerInputComponent->BindAxis("TurnRight", this, &ABasePlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasePlayer::AddControllerPitchInput);

	// Player Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::InputAxisMoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &ABasePlayer::InputAxisStrafe);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABasePlayer::OnFirePressed);
	PlayerInputComponent->BindAction("ReloadInput", IE_Pressed, this, &ABasePlayer::OnReloadPressed);
}

void ABasePlayer::HandleHurt(float ratio)
{
	Super::HandleHurt(ratio);
	UPlayerHUD* PlayerHUD = Cast<UPlayerHUD>(HUDWidget);
	if (PlayerHUD)
		PlayerHUD->SetHealth(ratio);

}

void ABasePlayer::HandleDeathStart(float ratio)
{
	Super::HandleDeathStart(ratio);
	UPlayerHUD* PlayerHUD = Cast<UPlayerHUD>(HUDWidget);
	PlayerHUD->SetHealth(ratio);
	DisableInput(PlayerController);

}

bool ABasePlayer::CanPickupHealth_Implementation()
{
	return true;
}

bool ABasePlayer::CanPickupAmmo_Implementation()
{
	return true;
}

void ABasePlayer::InputAxisMoveForward(float AxisValue)
{
	// Get control Rotation
	FRotator Break = GetControlRotation();
	FRotator Make(0., Break.Yaw, 0.);
	FVector WorldDirection = Make.Vector();

	// Move the actor forward
	AddMovementInput(WorldDirection, AxisValue);
	//AddMovementInput(FRotator(0., GetControlRotation().Yaw, 0).Vector(), AxisValue);
}

void ABasePlayer::InputAxisStrafe(float AxisValue)
{
	FRotator Break = GetControlRotation();
	FRotator Make(0., Break.Yaw + 90, 0.);
	FVector WorldDirection = Make.Vector();

	// Strafe the actor 
	AddMovementInput(WorldDirection, AxisValue);
}

void ABasePlayer::PlayerLost()
{
	OnPlayerLost.Broadcast();
	PlayerController->bShowMouseCursor = true;
	HUDWidget->RemoveFromParent();
	HUDWidget = nullptr;

}

void ABasePlayer::PlayerWin()
{
	DisableInput(PlayerController);
	HUDWidget->RemoveFromParent();
	HUDWidget = nullptr;
	UE_LOG(LogTemp, Log, TEXT("PlayerWin() triggered. HUD removed and input disabled."));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "PlayerWin() triggered. HUD removed and input disabled.");
}


