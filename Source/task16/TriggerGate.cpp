// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerGate.h"

ATriggerGate::ATriggerGate()
{
	OnActorBeginOverlap.AddDynamic(this, &ATriggerGate::OnOverlap);
}

void ATriggerGate::BeginPlay()
{
	Super::BeginPlay();
	Score = 0;
}

void ATriggerGate::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		Score++;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Score : %i"), Score));
	}
}