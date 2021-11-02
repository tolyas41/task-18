// Fill out your copyright notice in the Description page of Project Settings.


#include "SomeGameEngine.h"

void USomeGameEngine::Init(IEngineLoop* InEngineLoop)
{
#if UE_BUILD_DEVELOPMENT
	UE_LOG(LogTemp, Warning, TEXT("Game Engine Init"));
#endif
}

