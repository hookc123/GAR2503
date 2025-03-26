// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CodePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class END2025_API ACodePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ACodePlayerController();

protected:

	virtual void BeginPlay() override;

};
