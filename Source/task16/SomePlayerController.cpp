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

	PlayerTick(DeltaTime);
	UpdateRotation(DeltaTime);
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

}

void ASomePlayerController::Rotate(float Value)
{
	if (Value)
	{
		SetControlRotation((GetControlRotation() + FRotator(0, Value, 0)).Clamp());
		Character->AddActorLocalRotation(FRotator(0, Value, 0));
		
		UE_LOG(LogTemp, Warning, TEXT("Rotation :::: %s"), *GetControlRotation().ToString());
		UE_LOG(LogTemp, Warning, TEXT("CharRotation :::: %s"), *Character->GetActorRotation().ToString());

	}
}

void ASomePlayerController::MoveForward(float Value)
{
	//if ((this != NULL) && (Value != 0.0f))
	//{
	//}	
	if (Value)
	{
		//FRotator Rotation = Character->GetActorRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);

		//const FRotationMatrix Rotation();
		//const FVector Direction = Rotation.GetUnitAxis(EAxis::X);
		//Character->AddActorLocalOffset(Character->GetActorForwardVector() * Value * Character->MoveSpeed);
		//UE_LOG(LogTemp, Warning, TEXT("Direction :::: %s"), *(Character->GetActorForwardVector().ToString()));

		//Rotation.Normalize();
		//const FVector Direction = FRotationMatrix(Rotation).GetScaleVector();
		//const FVector Direction = Rotation.Vector();
		Character->SetActorRelativeLocation(Character->GetActorLocation() + Character->GetActorForwardVector() * Value * Character->MoveSpeed);

		//Character->AddMovementInput(Character->GetActorForwardVector(), Value, true);
		//FRotator Rotation = GetControlRotation();
		//Rotation.Normalize();
		////const FVector Direction = FRotationMatrix(Rotation).GetScaleVector();
		//const FVector Direction = Rotation.Vector();

		//const FRotator Rotation(0, GetControlRotation().Yaw / 2.0f, 0);
		//const FVector Direction = FVector()
		//Character->AddActorLocalOffset(FRotationMatrix(Rotation).GetScaleVector() * Value, true);
		//R.Yaw = FMath::Atan2(Y, X) * (180.f / PI);


		//const FRotator YawRotation(0, Rotation.Yaw, 0);

		//const FRotationMatrix cameraRotation(PlayerCameraManager->GetCameraRotation());
		//const FVector Direction = cameraRotation.GetScaledAxis(EAxis::X);
		//Character->AddActorLocalOffset(Direction * Value * Character->MoveSpeed);
		//Character->AddMovementInput(Character->GetActorForwardVector(), Value, true);
	}


	//AddMovementInput(GetActorForwardVector(), Value);
}

void ASomePlayerController::MoveRight(float Value)
{
	if (Value)
	{
		Character->SetActorRelativeLocation(Character->GetActorLocation() + Character->GetActorRightVector() * Value * Character->MoveSpeed);
		//Character->AddMovementInput(Character->GetActorForwardVector(), Value, true);
	}
	//AddMovementInput(GetActorRightVector(), Value);
}

void ASomePlayerController::Fire()
{
	Character->Fire();
	//if (ProjectileClass)
	//{
	//	FVector SpawnLoc = ProjectileSpawnPoint->GetComponentLocation();
	//	FRotator SpawnRot = ProjectileSpawnPoint->GetComponentRotation();
	//	AProjectile* ProjectileBullet = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLoc, SpawnRot);
	//}
}
