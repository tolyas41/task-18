// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Damage.h"
#include "Unit.generated.h"


class UBoxComponent;
class AProjectile;
class AHammerCollider;

UCLASS()
class TASK16_API AUnit : public APawn, public IDamage
{
	GENERATED_BODY()
	
public:	
	AUnit();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostActorCreated() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Causer")
	TSubclassOf<AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Causer")
	TSubclassOf<AHammerCollider> HammerClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	UBoxComponent* BoxComponent;

	UFUNCTION()
	virtual void OnDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DamageReceived")
	float DamageToApply = 50.0f;

private:
	float Health{ 100 };
};
