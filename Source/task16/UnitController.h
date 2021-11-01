// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitController.generated.h"

class AUnit;

UCLASS()
class TASK16_API AUnitController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	AUnitController();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	APawn* PlayerChar;

	AUnit* ControlledUnit;

	UFUNCTION()
	void UseAttack();
};
