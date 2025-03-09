// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FarmGame_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FARMGAME_API AFarmGame_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay() override;
};
