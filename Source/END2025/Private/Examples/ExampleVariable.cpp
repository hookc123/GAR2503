// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExampleVariable.h"

// Sets default values
AExampleVariable::AExampleVariable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Called when the game starts or when spawned
void AExampleVariable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExampleVariable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

