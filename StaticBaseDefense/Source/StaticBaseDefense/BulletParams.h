// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletParams.generated.h"

/**
 * 
 */
USTRUCT()
struct STATICBASEDEFENSE_API FBulletParams
{
	
	GENERATED_USTRUCT_BODY()

	//min mass should not be negative
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "3.0"))
		float Mass;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "10"))//Z direction
		float Gravity;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "20.0", ClampMax = "200.0"))
		float Acceleration;

	//min speed should not be negative
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "50.0"))
		float BaseVelocity;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0"))
		int	Damage;


	FBulletParams()
	{
		Mass = 0.0f;
		Gravity = 0.0f;
		Acceleration = 100.0f;
		BaseVelocity = 10.0f;
		Damage = 10;
	}
};
