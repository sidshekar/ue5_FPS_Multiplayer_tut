// Fill out your copyright notice in the Description page of Project Settings.


#include "EndZone.h"

#include "Components/BoxComponent.h"

#include "FPSCharacter.h"

#include "FPSGameMode.h"

// Sets default values
AEndZone::AEndZone(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore); // E Collsion Response
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->SetBoxExtent(FVector(200.0f));

	// set the box as the root component
	RootComponent = BoxComponent;


	// Otherwise the box collider component
	BoxComponent->SetHiddenInGame(false);

	// Simialar to actorBeginOverlap
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEndZone::HandleOverlap);

}

// Called when the game starts or when spawned
void AEndZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEndZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent,
							AActor* OtherActor,
							UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex,
							bool bFromSeep,
							const FHitResult& SweepResult) {


	if (HasAuthority()) {

		AFPSCharacter* mCharacter = Cast<AFPSCharacter>(OtherActor);

		if (mCharacter == nullptr) {

			return;
		}

		if (mCharacter->bIsCarryingObjective) {

			// GetAuthGameMode is only valid on server and doesnt exist on client
			AFPSGameMode* gMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

			if (gMode) {

				gMode->CompleteMission(mCharacter);

			}

		}
	}

}

// Called every frame
void AEndZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

