// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(cameraComponent != nullptr);

	cameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes.
	cameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// Enabling the pawn to control the camera's rotation.
	cameraComponent->bUsePawnControlRotation = true;
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

	// Player Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Player Rotation
	PlayerInputComponent->BindAxis("TurnRight", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

	// Player Jump
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);
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