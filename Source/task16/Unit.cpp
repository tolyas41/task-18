// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"
#include "SomeGameMode.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Damage.h"
#include "Projectile.h"
#include "HammerCollider.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"

AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

void AUnit::BeginPlay()
{
	Super::BeginPlay();
	CheckAttack();
}

void AUnit::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
#if UE_BUILD_DEVELOPMENT
	UE_LOG(LogTemp, Warning, TEXT("Unit %s is dead"), *(this->GetName()));
#endif
}

void AUnit::PostActorCreated()
{
	Super::PostActorCreated();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AUnit::OnDamage);
#if UE_BUILD_DEVELOPMENT
	UE_LOG(LogTemp, Warning, TEXT("Unit %s arrived"), *(this->GetName()));
#endif
}


void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnit::OnDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass() == HammerClass || OtherActor->GetClass() == CharProjectileClass)
	{
		DamageToApply = FMath::Min(Health, DamageToApply);
		Health -= DamageToApply;
#if UE_BUILD_DEVELOPMENT
		UE_LOG(LogTemp, Warning, TEXT("Health left %f, %s"), Health, *OtherActor->GetName());
#endif
		UWorld* TheWorld = GetWorld();
		if (TheWorld != nullptr)
		{
			AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
			ASomeGameMode* SomeGameMode = Cast<ASomeGameMode>(GameMode);
			SomeGameMode->OnDamageEvent.Broadcast();
		}
	}
	if (OtherActor->GetClass() == CharProjectileClass)
	{
		OtherActor->Destroy();
	}

	if (Health == 0)
	{
		Destroy();
		UWorld* TheWorld = GetWorld();
		if (TheWorld != nullptr)
		{
			AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
			ASomeGameMode* SomeGameMode = Cast<ASomeGameMode>(GameMode);
			SomeGameMode->OnDeathUnitEvent.Broadcast();
		}
	}
}

void AUnit::Attack()
{
	if (IsReadyToAttack)
	{
		PlayAnimMontage(AttackAnimation);
		FVector SpawnLoc = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRot = ProjectileSpawnPoint->GetComponentRotation();
		AProjectile* ProjectileBullet = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLoc, SpawnRot);
	}
}

void AUnit::CheckAttack()
{
	if (ProjectileClass && AttackAnimation)
	{
		IsReadyToAttack = true;
	}
	else
	{
#if UE_BUILD_DEVELOPMENT
		UE_LOG(LogTemp, Warning, TEXT("Attack animation and projectile didnt selected!"));
#endif
		IsReadyToAttack = false;
	}
}