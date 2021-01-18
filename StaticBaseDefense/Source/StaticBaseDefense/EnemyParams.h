// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EnemyParams.generated.h"
/**
 * Enemy parameters
 */
USTRUCT()
struct STATICBASEDEFENSE_API FEnemyParams
{
	GENERATED_USTRUCT_BODY()

		//min mass should not be negative
	UPROPERTY(EditAnywhere, meta = (ClampMin = "70.0", ClampMax = "1000.0"))
		float AllowAttackDistance;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "1.0", ClampMax = "10"))
		float AttackSpeed;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "50.0"))
		float MoveSpeed;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "5.0", ClampMax = "10.0"))
		int	Damage;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "20.0", ClampMax = "80.0"))
		int	HP;
	FEnemyParams()
	{
		AllowAttackDistance = 100.0;
		AttackSpeed = FMath::RandRange(3, 10);
		MoveSpeed = FMath::RandRange(20,50);
		Damage = FMath::RandRange(5, 10);
		HP = FMath::FRandRange(3, 30);
	}
};
