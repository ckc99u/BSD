// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponManager.h"

FWeaponManager::FWeaponManager(int _num)
{
	maxBullets = _num;
	bulletParams = FBulletParams();
}

FWeaponManager::~FWeaponManager()
{
	
	for (auto it : Bullets)
	{
		it->Destroy();
	}
	currentWeaponPtr = nullptr;
	Bullets.Empty();
	

}
//initialize weapon pool
void FWeaponManager::Initialize(UWorld* _w)
{
	for (int i = 0; i < maxBullets; i++) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABullet *_but = _w->SpawnActor<ABullet>(FVector(0, 0, 0), FRotator(0, 0, 0), SpawnInfo);
		Insert(_but);
	}
}
//update switch gun, update poll
void FWeaponManager::Update()
{

}

void FWeaponManager::Shoot(const FVector& _dir,const FVector &location, const FRotator &rot)
{
	currentWeaponPtr = OutBullet();
	currentWeaponPtr->Initialize(bulletParams);
	currentWeaponPtr->FireDirection(_dir, location);
}

void FWeaponManager::Insert(AWeaponBase * _obj)
{
	Bullets.Add(_obj);
}

AWeaponBase * FWeaponManager::OutBullet()
{
	if (currentIdx >= Bullets.Num())
		currentIdx = 0;
	return Bullets[currentIdx++];
}
