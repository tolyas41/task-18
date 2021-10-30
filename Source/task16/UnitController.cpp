// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitController.h"

#include "Kismet/GameplayStatics.h"

AUnitController::AUnitController()
{

}

void AUnitController::BeginPlay()
{
	Super::BeginPlay();
	PlayerChar = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SetFocus(PlayerChar, 0);
}

void AUnitController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("POSSES  %s"), *(InPawn->GetName()));
}

void AUnitController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerChar)
	{
		MoveToActor(PlayerChar);
	}
}

