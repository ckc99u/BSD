// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletBall = CreateDefaultSubobject<USphereComponent>("DefaultSceneRoot");

	BulletBall->InitSphereRadius(2.0f);

	ball = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	RootComponent = ball;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>mysphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere'"));
	if (mysphere.Succeeded())
		ball->SetStaticMesh(mysphere.Object);
	ball->SetWorldScale3D(FVector(0.2f,0.2f,0.2f));
	//use Uprimitive overlap.. 
		OnActorBeginOverlap.AddDynamic(this, &ABullet::OverlapObj);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

}
//overlap with Actor, apply damage
void ABullet::OverlapObj(AActor * ThisActor, AActor * OtherActor)
{
	if (Cast<AEnemyPawn>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(OtherActor, BulletType.Damage, nullptr, this, UDamageType::StaticClass());
	}
}

void ABullet::Initialize(const FBulletParams & _InParams)
{
	Super::Initialize(_InParams);
	Acceleration = _InParams.Acceleration;
	Veclocity = _InParams.BaseVelocity;
}

void ABullet::FireDirection(const FVector& _targetPoint, const FVector &_startPos)
{
	Super::FireDirection(_targetPoint, _startPos);
	target = _startPos;
	unitDireaction = _targetPoint;
	target += _targetPoint*Acceleration;
	ToggleVisibility(true);
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	if (bMoving) {
		
		target += unitDireaction * (Veclocity*DeltaTime + 0.5*(Acceleration*FMath::Pow(DeltaTime, 2)))*50;//s = va
		SetActorLocation(target);
		
		Acceleration*=0.95f;//decay
		if (Acceleration < 10)
		{
			bMoving = false;
			ToggleVisibility();
		}
	}
}
