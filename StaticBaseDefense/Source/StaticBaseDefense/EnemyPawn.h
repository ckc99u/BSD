// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include"StaticBaseDefense/PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "StaticBaseDefense/EnemyParams.h"
#include "EnemyPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIDelegate);
UCLASS()
class STATICBASEDEFENSE_API AEnemyPawn : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* CollisonCmp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* Mesh;
	void Initialize(const FVector &_playerLoc, const FVector &startLoc);
private:
	UFUNCTION()
		void MoveTo();
	UFUNCTION()
		void MoveToPlayer();
	UFUNCTION()
		void StartAttack();
	UFUNCTION()
		void AttackRate();

	FTimerHandle PatrolTimer;
	FTimerHandle TraceTimer;
	FTimerHandle AttackTimer;


private:
	int Healthy = 100;
	FVector PlayerLoc;
	bool bIsMoving = false;
	FVector nextPosition = FVector::FVector(0,0,0);//init is spawn position
	FVector nextPositionUnit ;
	FEnemyParams LocalParameters;

};
