// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TowerController.generated.h"

/**
 * 
 */
UCLASS()
class TASK16_API ATowerController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	TSubclassOf<AActor> TargetClass;

	void Aiming();

private:
	AActor* Target;
	TArray<AActor*> Enemies;
	float AttackDistance;
};
