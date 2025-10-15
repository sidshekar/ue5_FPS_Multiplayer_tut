// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

    // NetMulticast RPC
    // When called from the server
    // it gets sent on all clients
    // Including the server
    UFUNCTION(NetMulticast, Reliable)
    void MultiCastOnMissionComplete(APawn* instigatorPawn);
	
};
