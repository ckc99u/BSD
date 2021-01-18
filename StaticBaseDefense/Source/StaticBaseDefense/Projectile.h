#pragma once
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "StaticBaseDefense/WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.generated.h"
/*
2nd weapon should set as prefab in BP
*/
UCLASS()
class STATICBASEDEFENSE_API AProjectile : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void FireDirection(const FVector &_targetPoint, const FVector &_startPos);

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ExplosionCounter = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ProjectileDamage = 20.f;

	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* CollisionMesh = nullptr;


	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent* ExplosionForce = nullptr;
};
