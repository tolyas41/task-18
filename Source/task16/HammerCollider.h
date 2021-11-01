// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HammerCollider.generated.h"

DECLARE_EVENT(AHammerCollider, FOnHammerHitEvent)

class UCapsuleComponent;
UCLASS()
class TASK16_API AHammerCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	AHammerCollider();

	UFUNCTION()
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	FOnHammerHitEvent OnHammerHitEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* HammerCapsule;
};
