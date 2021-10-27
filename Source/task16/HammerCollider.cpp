// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "HammerCollider.h"

// Sets default values
AHammerCollider::AHammerCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HammerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hammer Collider"));
	SetRootComponent(HammerCapsule);
	//HammerCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//HammerCapsule->SetGenerateOverlapEvents(true);
	//HammerCapsule->SetSimulatePhysics(true);
	//HammerCapsule->SetVisibility(true);
}

// Called when the game starts or when spawned
void AHammerCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHammerCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

