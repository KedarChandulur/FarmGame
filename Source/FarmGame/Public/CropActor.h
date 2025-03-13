// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CropActor.generated.h"

UENUM(BlueprintType)
enum class ECropType : uint8
{
	Wheat UMETA(DisplayName = "Wheat"),
	Corn UMETA(DisplayName = "Corn")
};

UENUM(BlueprintType)
enum class ECropGrowthStage : uint8
{
	Seed UMETA(DisplayName = "Seed"),
	Growing UMETA(DisplayName = "Growing"),
	Harvestable UMETA(DisplayName = "Harvestable")
};

UCLASS()
class FARMGAME_API ACropActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACropActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void AdvanceGrowthStage();

private:
	UPROPERTY(EditAnywhere, Category = "Crop")
	ECropType cropType;

	UPROPERTY(EditAnywhere, Category = "Crop")
	ECropGrowthStage cropGrowthStage;

	// Time taken to reach the harvest stage
	UPROPERTY(EditAnywhere, Category = "Crop")
	float growthTime;

	// Timer helps handle the crop growth
	FTimerHandle growthTimerHandle;
};
