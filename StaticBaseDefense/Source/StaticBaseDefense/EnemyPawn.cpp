// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = SceneRoot;

	CollisonCmp = CreateDefaultSubobject<USphereComponent>("collision");
	CollisonCmp->InitSphereRadius(1.5f);
	CollisonCmp->SetupAttachment(SceneRoot);


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	Mesh->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>mysphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere'"));
	if (mysphere.Succeeded())
		Mesh->SetStaticMesh(mysphere.Object);

	Mesh->SetWorldScale3D(FVector(0.5f, 0.5f, 1.5f));
	LocalParameters = FEnemyParams();
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
//	SceneRoot->SetVisibility(false, true);// togglevisibility

}

float AEnemyPawn::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "to AI Damage");
	Healthy -= DamageAmount;
	
	if (Healthy <= 0)
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
		Destroy();
	}

	return 0.0f;
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (bIsMoving)
	{
		SetActorLocation( GetActorLocation()+ nextPositionUnit * LocalParameters.MoveSpeed*DeltaTime);
	}
}

void AEnemyPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void AEnemyPawn::Initialize(const FVector & _playerLoc, const FVector & startLoc)
{
	GetWorld()->GetTimerManager().SetTimer(PatrolTimer, this, &AEnemyPawn::MoveTo, 5.0, true, 0);
	GetWorld()->GetTimerManager().SetTimer(TraceTimer, this, &AEnemyPawn::MoveToPlayer, 7.0, true, 5);
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AEnemyPawn::StartAttack, 1, true, 2);
	PlayerLoc = _playerLoc;
	PlayerLoc.Z = startLoc.Z;
	nextPosition = startLoc;
	SetActorLocation(startLoc);
	Healthy = LocalParameters.HP;
	SceneRoot->SetVisibility(true, true);
	bIsMoving = true;
}

void AEnemyPawn::MoveTo()
{

	if (FVector::Distance(GetActorLocation(), nextPosition) < 100.0f )//goal is to player
	{
		nextPositionUnit = (PlayerLoc - GetActorLocation());//GetActorForwardVector();
		float ang = FMath::FRandRange(-90, 90);
		nextPosition  = nextPositionUnit.RotateAngleAxis(ang, FVector(0, 0, 1));
		nextPositionUnit  = nextPosition.GetSafeNormal();
	}
}

void AEnemyPawn::MoveToPlayer()
{
	if (FVector::Distance(GetActorLocation(), nextPosition) < 500.0f)//from patrol not restric
	{
		nextPosition = PlayerLoc;
		nextPositionUnit = (nextPosition - GetActorLocation()).GetSafeNormal();
	}
}
//check attack point
void AEnemyPawn::StartAttack()
{
	
	if (FVector::Distance(GetActorLocation(), PlayerLoc) < LocalParameters.AllowAttackDistance) 
	{
		bIsMoving = false;
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AEnemyPawn::AttackRate, LocalParameters.AttackSpeed, true, 0);
	}
}

void AEnemyPawn::AttackRate()
{
	UGameplayStatics::ApplyDamage(UGameplayStatics::GetPlayerController(GetWorld(), 0), LocalParameters.Damage, nullptr, this, UDamageType::StaticClass());
}




