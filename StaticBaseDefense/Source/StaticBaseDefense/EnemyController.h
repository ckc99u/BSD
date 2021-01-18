// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticBaseDefense/EnemyPawn.h"
#include "EnemyController.generated.h"

UCLASS()
class STATICBASEDEFENSE_API AEnemyController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyController();

///protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
public:	
	UFUNCTION(BlueprintCallable)
		void Create();
	UFUNCTION()
		void Spawner();
private:
	int Density = 1;

	FTimerHandle spawnDensityHandler;
	FVector PlayerPostion;

	AEnemyPawn *referenctPtr;



};
