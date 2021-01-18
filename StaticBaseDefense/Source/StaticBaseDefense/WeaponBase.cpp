// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWeaponBase::Initialize(const FBulletParams & _InParams)
{
	BulletType = _InParams;
}

void AWeaponBase::FireDirection(const FVector & _targetPoint, const FVector &_startPos)
{
	bMoving = true;
}


void AWeaponBase::ToggleVisibility(bool _newvis)
{
	RootComponent->SetVisibility(_newvis, true);
}

