// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"
#include "SomeGameMode.h"
#include "Components/BoxComponent.h"
#include "Damage.h"
#include "Projectile.h"
#include "HammerCollider.h"
#include "Kismet/GameplayStatics.h"

AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(BoxComponent);

}

void AUnit::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentHit.AddDynamic(this, &AUnit::OnDamage);
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
	if (OtherActor->GetClass() == ProjectileClass || OtherActor->GetClass() == HammerClass)
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
