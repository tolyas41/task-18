// Fill out your copyright notice in the Description page of Project Settings.


#include "SomeCharacter.h"
#include "SomeGameMode.h"
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

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	if (HammerClass)
	{
		HammerCollider = GetWorld()->SpawnActor<AHammerCollider>(HammerClass);
		HammerCollider->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("HammerCenter"));
		HammerCollider->SetOwner(this);
	}

	ASomeFactory* Factory = Cast<ASomeFactory>(UGameplayStatics::GetActorOfClass(GetWorld(), FactoryClass));
	if (Factory)
	{
		Factory->OnSpawnEvent.AddUFunction(this, FName("OnDamage"));
	}
	
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		ASomeGameMode* SomeGameMode = Cast<ASomeGameMode>(GameMode);
		SomeGameMode->OnDeathUnitEvent.AddUFunction(this, FName("Heal"), HealPower);
	}
}

void ASomeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetMesh()->IsPlaying())
	{
		GetMesh()->GetAnimInstance()->InitializeAnimation();
	}
}

void ASomeCharacter::Fire()
{
	if (ProjectileClass)
	{
		FVector SpawnLoc = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRot = ProjectileSpawnPoint->GetComponentRotation();
		AProjectile* ProjectileBullet = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLoc, SpawnRot);
	}
}

void ASomeCharacter::Attack()
{
	if (HammerAttackAnimation)
	{
		GetMesh()->PlayAnimation(HammerAttackAnimation, false);
	}
}

void ASomeCharacter::OnDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	int Chance = FMath::RandRange(0, 100);
	if (Chance > Avoidance)
	{
		DamageToApply = FMath::Min(Health, DamageToApply);
		Health -= DamageToApply;
#if UE_BUILD_DEVELOPMENT
		UE_LOG(LogTemp, Warning, TEXT("Char's health left (-) %f"), Health);
#endif
		if (Health == 0)
		{
			Destroy();
		}
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

