// Fill out your copyright notice in the Description page of Project Settings.


#include "CropActor.h"

// Sets default values
ACropActor::ACropActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	growthTime = (growthTime <= 0.0f) ? 5.0f : growthTime;
}

// Called when the game starts or when spawned
void ACropActor::BeginPlay()
{
	Super::BeginPlay();

	growthTime = (growthTime <= 0.0f) ? 5.0f : growthTime;
	
	cropGrowthStage = ECropGrowthStage::Seed;

	GetWorldTimerManager().SetTimer(growthTimerHandle, this, &ACropActor::AdvanceGrowthStage, growthTime, true);
}

void ACropActor::AdvanceGrowthStage()
{
	switch (cropGrowthStage)
	{
	case ECropGrowthStage::Seed:
		cropGrowthStage = ECropGrowthStage::Growing;
		break;

	case ECropGrowthStage::Growing:
		cropGrowthStage = ECropGrowthStage::Harvestable;
		GetWorldTimerManager().ClearTimer(growthTimerHandle);
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("Growth Stage Updated: %d"), static_cast<int>(cropGrowthStage));
}