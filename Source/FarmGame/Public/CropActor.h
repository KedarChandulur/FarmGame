// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
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
class FARMGAME_API ACropActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACropActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Interact_Implementation(AActor* interactedPlayer) override;

private:
	// Updates the growth stage to next stage.
	void AdvanceGrowthStage();

	// Method to trigger harvest functionality.
	void Harvest(AActor* interactedPlayer);

private:
	// Mesh for representation of the crop.
	UPROPERTY(VisibleAnywhere, Category = "Crop")
	UStaticMeshComponent* meshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Crop")
	//class UCapsuleComponent* collisionComponent;
	class UBoxComponent* collisionComponent;

	UPROPERTY(EditAnywhere, Category = "Crop")
	ECropType cropType;

	UPROPERTY(EditAnywhere, Category = "Crop")
	ECropGrowthStage cropGrowthStage;

	// Timer helps handle the crop growth
	FTimerHandle growthTimerHandle;

	// Time taken to reach the harvest stage
	UPROPERTY(EditAnywhere, Category = "Crop")
	float growthTime;
};
