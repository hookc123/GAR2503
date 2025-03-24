// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeBasePickup.h"
#include "Components/BoxComponent.h"


// Sets default values
ACodeBasePickup::ACodeBasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	boxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACodeBasePickup::BoundOverlap);

	SetRootComponent(boxCollision);
}

// Called when the game starts or when spawned
void ACodeBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACodeBasePickup::HandlePickup(AActor* otherActor, FHitResult hitResult)
{
}

void ACodeBasePickup::PostPickup()
{
	Destroy();
}

bool ACodeBasePickup::CanPickup(AActor* otherActor)
{
	return true;
}
// Called every frame
void ACodeBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACodeBasePickup::BoundOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	if (CanPickup(OtherActor))
	{
		HandlePickup(OtherActor, SweepResult);
		PostPickup();
	}
}