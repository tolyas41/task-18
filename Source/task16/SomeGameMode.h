// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SomeGameMode.generated.h"

DECLARE_EVENT(AUnit, FOnDamageEvent)
DECLARE_EVENT(AUnit, FOnDeathUnitEvent)

UCLASS()
class TASK16_API ASomeGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	FOnDamageEvent OnDamageEvent;
	FOnDeathUnitEvent OnDeathUnitEvent;

};
