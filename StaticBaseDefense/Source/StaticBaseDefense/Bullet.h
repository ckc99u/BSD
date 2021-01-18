// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "StaticBaseDefense/EnemyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "StaticBaseDefense/WeaponBase.h"
#include "Bullet.generated.h"
UCLASS()
class STATICBASEDEFENSE_API ABullet : public AWeaponBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void OverlapObj(class AActor* ThisActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Initialize(const FBulletParams &_InParams) override;//copy desired params 
	virtual void FireDirection(const FVector &_targetPoint, const FVector &_startPos) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* BulletBall;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* ball;
private:
	float Acceleration = 30.0f;
	float Veclocity = 0;
	FVector target;
	FVector unitDireaction;

};
