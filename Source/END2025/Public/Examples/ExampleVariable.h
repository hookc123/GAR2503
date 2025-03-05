// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleVariable.generated.h"

UCLASS(Abstract)
class END2025_API AExampleVariable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExampleVariable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Not Exposed to Blueprints
	bool CPlusPlusOnly;

	// Exposed as Read Only
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables|ReadOnly")
	bool VisibleAnywhere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Variables|ReadOnly")
	uint8 VisibleDefaultsOnly;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Variables|ReadOnly")
	int32 VisibleInstanceOnlyOdd;

	UPROPERTY(VisibleInstanceOnly, Category = "Variables|ReadOnly")
	int64 VisibleInstanceOnly;

	// Exposed as Read Write
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables|ReadWrite")
	float EditAnywhere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables|ReadWrite")
	FName EditDefaultsOnlyOdd;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Variables|ReadWrite")
	FString EditInstanceOnlyOdd;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|ReadWrite")
	FText EditDefaultsOnly;

	UPROPERTY(EditInstanceOnly, Category = "Variables|ReadWrite")
	FVector EditInstanceOnly;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
