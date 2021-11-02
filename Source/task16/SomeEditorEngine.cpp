// Fill out your copyright notice in the Description page of Project Settings.


#include "SomeEditorEngine.h"

void USomeEditorEngine::Init(IEngineLoop* InEngineLoop)
{
#if UE_BUILD_DEVELOPMENT
	UE_LOG(LogTemp, Warning, TEXT("Editor Engine Init"));
#endif
}
