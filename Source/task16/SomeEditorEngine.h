// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/EditorEngine.h"
#include "SomeEditorEngine.generated.h"

/**
 * 
 */
UCLASS()
class TASK16_API USomeEditorEngine : public UEditorEngine
{
	GENERATED_BODY()
	
public:
	virtual void Init(IEngineLoop* InEngineLoop) override;

};
