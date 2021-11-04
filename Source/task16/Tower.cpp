// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Projectile.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	//StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	SetRootComponent(ProjectileSpawnPoint);
	//ProjectileSpawnPoint->SetupAttachment(StaticMeshComponent);
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileClass) 
	{
		FTimerHandle FireTimerHandle;
		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATower::Fire, 0.5f, true, 2.0f);
	}
}

void ATower::PostActorCreated()
{
	Super::PostActorCreated();

	FVector SpawnLoc = ProjectileSpawnPoint->GetComponentLocation();
	SpawnLoc.Set(SpawnLoc.X, SpawnLoc.Y, SpawnLoc.Z - 150.0f);
	FRotator SpawnRot = ProjectileSpawnPoint->GetComponentRotation();
	AActor* TowerMesh = GetWorld()->SpawnActor<AActor>(TowerMeshClass, SpawnLoc, SpawnRot);
}

void ATower::Fire()
{
	FVector SpawnLoc = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRot = ProjectileSpawnPoint->GetComponentRotation();
	AProjectile* ProjectileBullet = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLoc, SpawnRot);
}