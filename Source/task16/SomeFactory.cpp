// Fill out your copyright notice in the Description page of Project Settings.


#include "SomeFactory.h"
#include "Unit.h"
#include "TimerManager.h"
#include "SomeGameMode.h"
#include "Kismet/GameplayStatics.h"

ASomeFactory::ASomeFactory()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASomeFactory::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle MemberTimerHandle;
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ASomeFactory::SpawnUnit, 2.7f, true, 2.0f);
}

void ASomeFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASomeFactory::SpawnUnit()
{
	SpawnLocation = GetActorLocation() + FVector(FMath::RandRange(-500.0f, 500.0f), FMath::RandRange(-500.0f, 500.0f), 0);
	GetWorld()->SpawnActor<AUnit>(UnitToSpawn, SpawnLocation, FRotator(0, 225.0f, 0));
}
