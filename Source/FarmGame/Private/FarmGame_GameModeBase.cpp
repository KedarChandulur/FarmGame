// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmGame_GameModeBase.h"

void AFarmGame_GameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello world, this is FarmGame_GameModeBase"));
}