// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"
#include "GameFramework/PlayerController.h"
#include "CropActor.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// First line trace will be performed and once a object is hit, interaction is performed on that specific object.
void UInteractComponent::Interact()
{
	// Getting the owner pawn to retrive the controller from it.
	APawn* ownerPawn = Cast<APawn>(GetOwner());

	if (ownerPawn == nullptr)
	{
		check(false);
		return;
	}

	// After successful retrival of the pawn, grab the controller from it.
	APlayerController* playerController = Cast<APlayerController>(ownerPawn->GetController());

	if (playerController == nullptr)
	{
		check(false);
		return;
	}

	// Retrive the view point(camera) position from player controller.
	FVector start;
	FRotator rotation;
	playerController->GetPlayerViewPoint(start, rotation);

	// Max line travel distance from camera.
	constexpr double lineTravelDistance = 500;
	FVector end = start + (rotation.Vector() * lineTravelDistance); // Vector() basically returns the forward direction.

	// Performing the line trace.
	FHitResult hitresult;
	FCollisionQueryParams collisionQueryParams;
	collisionQueryParams.AddIgnoredActor(GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(hitresult, start, end, ECC_Visibility, collisionQueryParams))
	{
		AActor* hitactor = hitresult.GetActor();

		if (hitactor != nullptr && hitactor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			// Actual interaction happening here.
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Hit: %s"), *hitactor->GetActorLabel())); // GetActorLabel() - Only available in dev builds.

			IInteractable::Execute_Interact(hitactor);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No object hit."));
		}
	}
}