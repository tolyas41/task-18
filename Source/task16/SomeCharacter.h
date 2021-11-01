// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damage.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SomeCharacter.generated.h"

class AProjectile;
class ASomeFactory;
class AHammerCollider;
class UAnimationAsset;

DECLARE_EVENT(ASomeCharacter, FHealEvent)

UCLASS()
class TASK16_API ASomeCharacter : public ACharacter, public IDamage
{
	GENERATED_BODY()

public:
	ASomeCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void StopAnimation();
	UFUNCTION()
	void Fire();
	UFUNCTION()
	void Attack();
	UFUNCTION()
	virtual void OnDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;
	UFUNCTION()
	void Heal(float HealAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullets")
	TSubclassOf<AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Factory")
	TSubclassOf<ASomeFactory> FactoryClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hammer")
	TSubclassOf<AHammerCollider> HammerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hammer")
	UAnimationAsset* HammerAttackAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hammer")
	UAnimationAsset* HammerReturnAnimation;
	UPROPERTY()
	AHammerCollider* HammerCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float MoveSpeed = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float RotateSpeed = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Healing")
	float HealPower = 8.0f;

	FHealEvent OnHealEvent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float DamageToApply = 15.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	int32 Avoidance = 50;

private:
	float Health{ 100 };
};
