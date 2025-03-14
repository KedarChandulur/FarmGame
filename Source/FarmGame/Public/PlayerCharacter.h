// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FARMGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Helps move player forward and backward
	void MoveForward(float value);

	// Helps move player right and left
	void MoveRight(float value);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void HandleInteraction();

private:
	// A Basic FPS camera.
	UPROPERTY(BlueprintReadOnly, Category = "Camera Component", meta = (AllowPrivateAccess=true))
	class UCameraComponent* cameraComponent;

	// Interaction component, contains specific step(s) through which the object will be interacted.
	UPROPERTY(BlueprintReadOnly, Category = "Interact Component", meta = (AllowPrivateAccess=true))
	class UInteractComponent* interactionComponent;
};
