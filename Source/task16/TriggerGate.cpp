// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerGate.h"

ATriggerGate::ATriggerGate()
{
	OnActorBeginOverlap.AddDynamic(this, &ATriggerGate::OnOverlap);
}

void ATriggerGate::BeginPlay()
{
	Super::BeginPlay();
	score = 0;
}

void ATriggerGate::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		score++;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Score : %i"), score));
	}
}