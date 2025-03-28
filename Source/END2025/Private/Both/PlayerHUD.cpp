// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "../END2025.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/SlateBlueprintLibrary.h>
#include "Components/TextBlock.h"

void UPlayerHUD::SetHealth(float p)
{
	if (!HealthBar) return;
	HealthBar->SetPercent(p);
}

void UPlayerHUD::SetAmmo(float c, float m)
{
    CurrentAmmo->SetText(FText::AsNumber(c));
    MaxAmmo->SetText(FText::AsNumber(m));
}

FVector UPlayerHUD::GetDestination()
{
	return EndPoint;
}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	UpdateCrosshair();
}

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

    if (Crosshair)
    {
        // Get the dynamic material from the Crosshair image
        DynamicMaterial = Crosshair->GetDynamicMaterial();

        if (DynamicMaterial)
        {
            UE_LOG(Game, Warning, TEXT("Dynamic Material successfully assigned!"));
        }
        else
        {
            UE_LOG(Game, Error, TEXT("Failed to retrieve Dynamic Material from Crosshair!"));
        }
    }
    else
    {
        UE_LOG(Game, Error, TEXT("Crosshair Image is NULL in PlayerHUD!"));
    }

}

void UPlayerHUD::UpdateCrosshair()
{
    APlayerController* PlayerController = GetOwningPlayer();
    if (!PlayerController) return;

    FVector2D ScreenPosition;
    FVector WorldPosition, WorldDirection;

    // Get crosshair position in screen space
    if (Crosshair)
    {
        ScreenPosition = GetCrosshairScreenPosition();
    }

    // Convert screen position to world space
    if (PlayerController->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldPosition, WorldDirection))
    {
        // Set End Point for Line Trace
        EndPoint = WorldPosition + (WorldDirection * 100000.0f); 


        // Define object types to trace
        FCollisionObjectQueryParams ObjectTypes;
        ObjectTypes.AddObjectTypesToQuery(ECC_Pawn);
        ObjectTypes.AddObjectTypesToQuery(ECC_WorldDynamic);

        // Define actors to ignore
        FHitResult HitResult;
        FCollisionQueryParams TraceParams;
        TraceParams.AddIgnoredActor(PlayerController->GetPawn()); // Ignore the player

		//DrawDebugLine(GetWorld(), WorldPosition, EndPoint, FColor::Red, false, 0.1f, 0, 1.0f);

        // Perform Line Trace
        bool bHit = GetWorld()->LineTraceSingleByObjectType(
            HitResult,
            WorldPosition,
            EndPoint,
            ObjectTypes,
            TraceParams
        );

		if (bHit)
		{
			ECollisionChannel Channel = HitResult.GetComponent()->GetCollisionObjectType();
			EndPoint = HitResult.ImpactPoint;
			if (Channel==ECC_Pawn)
                DynamicMaterial->SetVectorParameterValue(ColorName, DangerColor);
            else 
                DynamicMaterial->SetVectorParameterValue(ColorName, SafeColor);
		}
		else 
            DynamicMaterial->SetVectorParameterValue(ColorName, SafeColor);
    }
}

FVector2D UPlayerHUD::GetCrosshairScreenPosition()
{
    if (!Crosshair)
    {
		return FVector2D(0, 0);
    }

	// Get the cached geometry of the crosshair
    FGeometry CrosshairGeometry = Crosshair->GetCachedGeometry();

    // Convert Local Position (0,0) to Viewport Position
    FVector2D ViewportPosition;
    FVector2D PixelPosition;
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), CrosshairGeometry, FVector2D(0, 0), PixelPosition, ViewportPosition);
    FVector2D CrosshairSize = USlateBlueprintLibrary::GetAbsoluteSize(CrosshairGeometry);

    // Return Center Position of Crosshair in Screen Space
    return PixelPosition + (CrosshairSize * 0.5f);
}
