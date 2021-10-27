// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damage.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamage : public UInterface
{
	GENERATED_BODY()
};

class TASK16_API IDamage
{
	GENERATED_BODY()

public:
	virtual void OnDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) = 0;
};
