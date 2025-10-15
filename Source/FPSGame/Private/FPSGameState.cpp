// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"

#include "FPSPlayerController.h"

void AFPSGameState::MultiCastOnMissionComplete_Implementation(APawn* instigatorPawn){

	// Get all the Player Controller on the Client 
	for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; it++) {

		// Get the Controller
		AFPSPlayerController* pController = Cast<AFPSPlayerController>(it->Get());

		// Check if controller exists and is local
		if (pController && pController->IsLocalController()) {

			// BP Implementable Event
			pController->OnMissionCompleted(instigatorPawn);

			APawn* mPawn = pController->GetPawn();

			if (mPawn) {

				mPawn->DisableInput(pController);
			}
		}

	}

}
