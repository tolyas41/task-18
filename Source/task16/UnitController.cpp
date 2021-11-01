// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitController.h"
#include "Unit.h"
#include "TimerManager.h"

#include "Kismet/GameplayStatics.h"

AUnitController::AUnitController()
{

}

void AUnitController::BeginPlay()
{
	Super::BeginPlay();
	PlayerChar = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SetFocus(PlayerChar, 0);

	FTimerHandle MemberTimerHandle;
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AUnitController::UseAttack, 2.0f, true, 2.0f);

}

void AUnitController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("POSSES  %s"), *(InPawn->GetName()));
	ControlledUnit = Cast<AUnit>(InPawn);
}

void AUnitController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//MoveToLocation(FVector(394.785126, 175.686935, 79.641167));
	if (PlayerChar)
	{

		//MoveToActor(PlayerChar);
		//GetPawn()->AddMovementInput(PlayerChar->GetActorLocation());
	}
}

void AUnitController::UseAttack()
{
	ControlledUnit->Attack();
}
