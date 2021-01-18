// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticBaseDefense/BulletParams.h"
#include "WeaponBase.generated.h"

UCLASS()
class STATICBASEDEFENSE_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();
	virtual void Initialize(const FBulletParams &_InParams);//copy desired params 
	virtual void FireDirection(const FVector &_targetPoint, const FVector &_startPos);
	virtual void ToggleVisibility(bool _newvis = false);



protected:
	FBulletParams BulletType;
	bool bMoving = false;
	
};
