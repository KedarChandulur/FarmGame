// Fill out your copyright notice in the Description page of Project Settings.


#include "CropActor.h"
#include "BudgetComponent.h"
#include "PlayerCharacter.h"
//#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ACropActor::ACropActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	growthTime = (growthTime <= 0.0f) ? 5.0f : growthTime;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = meshComponent;

	// Capsule Collider Init
	//collisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	//collisionComponent->SetupAttachment(MeshComponent); // Attach to the mesh
	//collisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//collisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	//collisionComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// Box Collider Init
	collisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	collisionComponent->SetupAttachment(meshComponent);

	collisionComponent->SetBoxExtent(FVector(128.0f, 128.0f, 128.0f));

	collisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	collisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	collisionComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

// Called when the game starts or when spawned
void ACropActor::BeginPlay()
{
	Super::BeginPlay();

	growthTime = (growthTime <= 0.0f) ? 5.0f : growthTime;
	
	cropGrowthStage = ECropGrowthStage::Seed;

	GetWorldTimerManager().SetTimer(growthTimerHandle, this, &ACropActor::AdvanceGrowthStage, growthTime, true);
}

void ACropActor::Interact_Implementation(AActor* interactedPlayer)
{
	if (interactedPlayer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interacted player parameter is missing."));
		return;
	}

	Harvest(interactedPlayer);
}

void ACropActor::Harvest(AActor* interactedPlayer)
{
	if (cropGrowthStage == ECropGrowthStage::Harvestable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Crop harvested: %s"), *GetActorLabel()); // GetActorLabel() only available in dev builds.

		if (interactedPlayer == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Interacted actor in crop harvest is missing."));
			check(false);
			return;
		}

		APlayerCharacter* player = Cast<APlayerCharacter>(interactedPlayer);

		if (player == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Interacted player in crop harvest is missing."));
			check(false);
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("Interacted player in crop harvest %s"), *player->GetActorLabel()); // GetActorLabel() only available in dev builds.

		const int harvestValue = 100;

		player->AddMoneyToBudget(harvestValue);

		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Crop is not ready to be harvested!"));
	}
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

	default:
		UE_LOG(LogTemp, Warning, TEXT("Default called on Advanced Growth Stage"));
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("Growth Stage Updated: %d"), static_cast<int>(cropGrowthStage));
}