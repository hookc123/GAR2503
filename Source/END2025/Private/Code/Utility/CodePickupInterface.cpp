// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Utility/CodePickupInterface.h"

// Add default functionality here for any ICodePickupInterface functions that are not pure virtual.

bool ICodePickupInterface::CanPickupHealth_Implementation()
{
	return false;
}

bool ICodePickupInterface::CanPickupAmmo_Implementation()
{
	return false;
}
