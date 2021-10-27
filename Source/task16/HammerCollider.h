// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HammerCollider.generated.h"

class UCapsuleComponent;
UCLASS()
class TASK16_API AHammerCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	AHammerCollider();

	UPROPERTY()
	UCapsuleComponent* HammerCapsule;
};
