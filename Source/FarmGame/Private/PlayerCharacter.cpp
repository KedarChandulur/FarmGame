// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hello this is PlayerCharacter"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
}

void APlayerCharacter::MoveForward(float value)
{
	// Getting the controller's rotation.
	FRotationMatrix controllerRotation{ Controller->GetControlRotation() };

	// Getting the forward direction.
	FVector direction = controllerRotation.GetScaledAxis(EAxis::Type::X);

	AddMovementInput(direction, value);
}

void APlayerCharacter::MoveRight(float value)
{
	// Getting the controller's rotation.
	FRotationMatrix controllerRotation{ Controller->GetControlRotation() };

	// Getting the right direction.
	FVector direction = controllerRotation.GetScaledAxis(EAxis::Type::Y);

	AddMovementInput(direction, value);
}