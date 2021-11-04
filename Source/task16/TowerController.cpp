// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerController.h"
#include "Kismet/GameplayStatics.h"

void ATowerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerController::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle AimTimerHandle;
	GetWorldTimerManager().SetTimer(AimTimerHandle, this, &ATowerController::Aiming, 5.0f, true, 2.0f);

}

void ATowerController::Aiming()
{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetClass, Enemies);
		Target = UGameplayStatics::FindNearestActor(GetPawn()->GetActorLocation(), Enemies, AttackDistance);
	if (Target)
	{
		SetFocus(Target);
		UE_LOG(LogTemp, Warning, TEXT("AIM  %s"), *(Target->GetName()));
	}

	if (!Target)
	{
	}
}












/**
 *	Find all Actors in the world of the specified class.
 *	This is a slow operation, use with caution e.g. do not use every frame.
 *	@param	ActorClass	Class of Actor to find. Must be specified or result array will be empty.
 *	@param	OutActors	Output array of Actors of the specified class.
 */

	/**
 *	Returns an Actor nearest to Origin from ActorsToCheck array.
 *	@param	Origin			World Location from which the distance is measured.
 *	@param	ActorsToCheck	Array of Actors to examine and return Actor nearest to Origin.
 *	@param	Distance	Distance from Origin to the returned Actor.
 *	@return				Nearest Actor.
 */