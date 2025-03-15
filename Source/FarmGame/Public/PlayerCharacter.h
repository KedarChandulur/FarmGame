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
	void MoveForward(const float value);

	// Helps move player right and left
	void MoveRight(const float value);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddMoneyToBudget(const int amount) const;

	void SubstractMoneyToBudget(const int amount) const;
private:
	void HandleInteraction();

private:
	// A Basic FPS camera.
	UPROPERTY(BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	class UCameraComponent* cameraComponent;

	// Interaction component, contains specific step(s) through which the object will be interacted.
	UPROPERTY(BlueprintReadOnly, Category = "Interact", meta = (AllowPrivateAccess = true))
	class UInteractComponent* interactionComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Budget", meta = (AllowPrivateAccess = true))
	class UBudgetComponent* budgetComponent;
};
