// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "PlayerHUD.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class END2025_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:



	UFUNCTION(BlueprintCallable)
	void SetHealth(float p);

	UFUNCTION(BlueprintCallable)
	void SetAmmo(float c, float m);

	UFUNCTION(BlueprintPure)
	FVector GetDestination();

    virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;


    UPROPERTY(meta = (BindWidget))
    UTextBlock* CurrentAmmo;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MaxAmmo;



protected:

    UPROPERTY(BlueprintReadOnly, Category = HUD, meta = (BindWidget))
	class UProgressBar* HealthBar;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD, meta = (BindWidget))
    UImage* Crosshair;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    UMaterialInstanceDynamic* DynamicMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    FName ColorName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    FLinearColor SafeColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    FLinearColor DangerColor;

    virtual void NativeConstruct() override;
    void UpdateCrosshair();

private:
	FVector EndPoint;

    UFUNCTION(BlueprintCallable, Category = "HUD")
    FVector2D GetCrosshairScreenPosition();


};
