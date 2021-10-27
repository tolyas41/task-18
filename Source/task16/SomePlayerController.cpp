// Fill out your copyright notice in the Description page of Project Settings.


#include "SomePlayerController.h"
#include "SomeCharacter.h"

ASomePlayerController::ASomePlayerController()
{

}

void ASomePlayerController::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ASomeCharacter>(GetPawnOrSpectator());
	SetViewTarget(Character);

}
void ASomePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//PlayerTick(DeltaTime);
	//UpdateRotation(DeltaTime);
}


void ASomePlayerController::OnPossess(APawn* aPawn)
{
#if UE_BUILD_DEVELOPMENT
	UE_LOG(LogTemp, Warning, TEXT("Posses DONE"));
#endif
}

void ASomePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Rotate", this, &ASomePlayerController::Rotate);
	InputComponent->BindAxis("MoveForward", this, &ASomePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASomePlayerController::MoveRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ASomePlayerController::Fire);
	InputComponent->BindAction("Attack", IE_Pressed, this, &ASomePlayerController::Attack);

}

void ASomePlayerController::Rotate(float Value)
{
	if (Value)
	{
		SetControlRotation((GetControlRotation() + FRotator(0, Value, 0)).Clamp());
	}
}

void ASomePlayerController::MoveForward(float Value)
{
	if (Value)
	{
		Character->SetActorRelativeLocation(Character->GetActorLocation() + Character->GetActorForwardVector() * Value * Character->MoveSpeed);
	}
}

void ASomePlayerController::MoveRight(float Value)
{
	if (Value)
	{
		Character->SetActorRelativeLocation(Character->GetActorLocation() + Character->GetActorRightVector() * Value * Character->MoveSpeed);
	}
}

void ASomePlayerController::Fire()
{
	Character->Fire();
}

void ASomePlayerController::Attack()
{
	Character->Attack();
}