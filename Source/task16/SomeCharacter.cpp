// Fill out your copyright notice in the Description page of Project Settings.


#include "SomeCharacter.h"
#include "SomeGameMode.h"
#include "Components/InputComponent.h"
#include "Projectile.h"
#include "SomeFactory.h"
#include "Kismet/GameplayStatics.h"


ASomeCharacter::ASomeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

	bUseControllerRotationYaw = false;
}

void ASomeCharacter::BeginPlay()
{
	Super::BeginPlay();

	factory->OnSpawnEvent.AddUFunction(this, FName("OnDamage"));
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

}

void ASomeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Rotate", this, &ASomeCharacter::Rotate);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASomeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASomeCharacter::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASomeCharacter::Fire);
}

void ASomeCharacter::Rotate(float Value)
{
	if (Value)
	{
		AddActorLocalRotation(FRotator(0, Value, 0));
	}
}

void ASomeCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASomeCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
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
