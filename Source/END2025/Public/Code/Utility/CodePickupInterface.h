// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CodePickupInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCodePickupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class END2025_API ICodePickupInterface
{
	GENERATED_BODY()



	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	bool CanPickupHealth();
	virtual bool CanPickupHealth_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	bool CanPickupAmmo();
	virtual bool CanPickupAmmo_Implementation();

};
