// Fill out your copyright notice in the Description page of Project Settings.
#include "BudgetComponent.h"

// Sets default values for this component's properties
UBudgetComponent::UBudgetComponent()
	:currentBudget(1000)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UBudgetComponent::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Initial Budget: %d"), currentBudget));
}

void UBudgetComponent::AddMoney(const int amount)
{
	check(amount > -1);

	currentBudget += amount;
}

void UBudgetComponent::SubstractMoney(const int amount)
{
	check(amount > -1);

	if (HasEnoughMoney(amount))
	{
		currentBudget -= amount;
	}
}