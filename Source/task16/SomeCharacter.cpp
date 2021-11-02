// Fill out your copyright notice in the Description page of Project Settings.


#include "SomeCharacter.h"
#include "SomeGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Projectile.h"
#include "SomeFactory.h"
#include "HammerCollider.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"

ASomeCharacter::ASomeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

void ASomeCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ASomeCharacter::OnDamage);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	if (HammerClass)
	{
		HammerCollider = GetWorld()->SpawnActor<AHammerCollider>(HammerClass);
		HammerCollider->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("HammerCenter"));
		HammerCollider->SetOwner(this);

		HammerCollider->OnHammerHitEvent.AddUFunction(this, FName("StopAnimation"));
	}
	
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		ASomeGameMode* SomeGameMode = Cast<ASomeGameMode>(GameMode);
		SomeGameMode->OnDeathUnitEvent.AddUFunction(this, FName("Heal"), HealPower);
	}

	CheckAttack();
	CheckProjectile();
}

void ASomeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASomeCharacter::Fire()
{
	if (IsReadyToFire && !IsAttackOnCooldown)
	{
		IsAttackOnCooldown = true;
		PlayAnimMontage(FireAttackAnimation);
		FVector SpawnLoc = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRot = ProjectileSpawnPoint->GetComponentRotation();
		AProjectile* ProjectileBullet = GetWorld()->SpawnActor<AProjectile>(CharProjectileClass, SpawnLoc, SpawnRot);
	}
	Cooldown();
}

void ASomeCharacter::Attack()
{
	if (IsReadyToAttack && !IsAttackOnCooldown)
	{
		IsAttackOnCooldown = true;
		PlayAnimMontage(HammerAttackAnimation);
	}
	Cooldown();
}

void ASomeCharacter::OnDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass() == ProjectileClass)
	{
		DamageToApply = FMath::Min(Health, DamageToApply);
		Health -= DamageToApply;
#if UE_BUILD_DEVELOPMENT
		UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);
#endif
		OtherActor->Destroy();
	}
	if (Health == 0)
	{
		Destroy();
	}
}

void ASomeCharacter::Heal(float HealAmount)
{
	if (Health < 100)
	{
		Health += FMath::Min(100 - Health, HealAmount);
#if UE_BUILD_DEVELOPMENT
		UE_LOG(LogTemp, Warning, TEXT("Char's health left (+) %f"), Health);
#endif
	}
}

void ASomeCharacter::StopAnimation()
{
	if (IsReadyToAttack)
	{
		PlayAnimMontage(HammerReturnAnimation);
	}
}

void ASomeCharacter::CheckProjectile()
{
	if (CharProjectileClass && FireAttackAnimation)
	{
		IsReadyToFire = true;
	}
	else
	{
#if UE_BUILD_DEVELOPMENT
		UE_LOG(LogTemp, Warning, TEXT("Projectile and animation didnt selected!"));
#endif
		IsReadyToFire = false;
	}
}

void ASomeCharacter::CheckAttack()
{
	if (HammerAttackAnimation && HammerReturnAnimation)
	{
		IsReadyToAttack = true;
	}
	else
	{
#if UE_BUILD_DEVELOPMENT
		UE_LOG(LogTemp, Warning, TEXT("Attack animations didnt selected!"));
#endif
		IsReadyToAttack = false;
	}
}

void ASomeCharacter::Cooldown()
{
	if (!GetWorldTimerManager().IsTimerActive(AttackCooldownHandle))
	{
		GetWorldTimerManager().SetTimer(AttackCooldownHandle, this, &ASomeCharacter::AttackOnCooldown, 0.1f, false, AttackCooldown);
	}
}

void ASomeCharacter::AttackOnCooldown()
{
	IsAttackOnCooldown = false;
}