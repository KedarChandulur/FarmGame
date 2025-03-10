// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BudgetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMGAME_API UBudgetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBudgetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Budget")
	FORCEINLINE int GetBudget() const
	{
		return currentBudget;
	}

	UFUNCTION(BlueprintCallable, Category = "Budget")
	FORCEINLINE bool HasEnoughMoney(const int amount) const
	{
		return currentBudget >= amount;
	}

private:
	UFUNCTION(BlueprintCallable, Category = "Budget")
	void AddMoney(const int amount);

	UFUNCTION(BlueprintCallable, Category = "Budget")
	void SubstractMoney(const int amount);

private:
	UPROPERTY(EditAnywhere, Category = "Budget")
	int currentBudget;
};
