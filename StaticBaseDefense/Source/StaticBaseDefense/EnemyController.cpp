// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPostion = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	GetWorld()->GetTimerManager().SetTimer(spawnDensityHandler, this, &AEnemyController::Spawner, 10.0, true, 0);
}

void AEnemyController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
}



void AEnemyController::Create()
{

}

void AEnemyController::Spawner()
{
	
	FVector Location(500.0f, 500.0f, 75.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < Density; i++) 
	{
		Location.X += FMath::RandRange(-200, 100);
		Location.Y += FMath::RandRange(-200, 100);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		referenctPtr = GetWorld()->SpawnActor<AEnemyPawn>(Location, Rotation, SpawnInfo);
		referenctPtr->Initialize(PlayerPostion, Location);///
	}

}


