// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CodeMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class END2025_API ACodeMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ACodeMenuPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> MenuClass;

protected:
	
	virtual void BeginPlay() override;

private:

};
