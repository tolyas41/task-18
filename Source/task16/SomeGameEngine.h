// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameEngine.h"
#include "SomeGameEngine.generated.h"

/**
 * 
 */
UCLASS()
class TASK16_API USomeGameEngine : public UGameEngine
{
	GENERATED_BODY()
	
public:
	virtual void Init(IEngineLoop* InEngineLoop) override;

};
