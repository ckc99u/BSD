// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StaticBaseDefense/Bullet.h"
#include "StaticBaseDefense/EnemyPawn.h"
#include "CoreMinimal.h"

/**
 * An objet that manage thw weapons especially the order of spawn;
 */
class STATICBASEDEFENSE_API FWeaponManager
{
public:
	FWeaponManager(int _num);
	~FWeaponManager();
	void Initialize(UWorld* _w);//initialize weapons
	void Update();
	void Shoot(const FVector &_dir, const FVector &location, const FRotator &rot);
	UPROPERTY(EditDefaultsOnly, Category = m_weaponMesh)
		TSubclassOf<AWeaponBase> currentWeapon;
private: 

	AWeaponBase* currentWeaponPtr;

	TArray<AWeaponBase*>Bullets;//create a matrix
	void Insert(AWeaponBase *_obj);
	AWeaponBase* OutBullet();
	FBulletParams bulletParams;
	int currentIdx = 0;
	int maxBullets = 50;

};
