// Fill out your copyright notice in the Description page of Project Settings.


#include "BSDPawn.h"

/*
playerController control pawn
*/
ABSDPawn::ABSDPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create Components Initialize
	m_weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("DefaultSceneRoot");
	m_cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("m_cameraArm"));
	m_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	/*static ConstructorHelpers::FObjectFinder<UStaticMesh>mysphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere'"));

	if (mysphere.Succeeded())
		m_weaponMesh->SetStaticMesh(mysphere.Object);

	m_weaponMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));*/
	FVector currentLoc = GetActorLocation();
	currentLoc.Z -= 50;
	m_weaponMesh->SetWorldLocation(currentLoc);
	RootComponent = m_weaponMesh;
	m_cameraArm->SetupAttachment(m_weaponMesh);


	m_cameraArm->TargetArmLength = 30.0f;
	m_cameraArm->bEnableCameraLag = true;
	m_cameraArm->bUsePawnControlRotation = true;
	m_cameraArm->CameraLagSpeed = 2.0f;


	m_camera->SetupAttachment(m_cameraArm, USpringArmComponent::SocketName);
	m_camera->SetRelativeLocation(FVector(-50.0f, 0.0f, 0.0f));
	m_camera->bUsePawnControlRotation = false;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}



void ABSDPawn::PreInitializeComponents()
{
	//m_fweaponManager = new FWeaponManager(20);
	//m_fweaponManager->Initialize(GetWorld());
}

void ABSDPawn::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	delete m_fweaponManager;
	m_fweaponManager = nullptr;
}

// Called to bind functionality to input
void ABSDPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABSDPawn::Fire);
	PlayerInputComponent->BindAxis("Pitch", this, &ABSDPawn::PitchCamera);
	PlayerInputComponent->BindAxis("Yaw", this, &ABSDPawn::YawCamera);

}

void ABSDPawn::Fire()
{

	FVector cameraLoc;
	FRotator cameraRot;
	GetActorEyesViewPoint(cameraLoc, cameraRot);
	// transform muzzleoffset from camera space to world space
	FVector muzzleLoc = cameraLoc + FTransform(cameraRot).TransformVector(m_Offset);
	FRotator muzzleRot = cameraRot;
	muzzleRot.Pitch += -5.0f;

	m_fweaponManager->Shoot(muzzleRot.Vector(), muzzleLoc, muzzleRot);
	if (!ensure(m_projectileBP)) return;
	auto projectile = GetWorld()->SpawnActor<AProjectile>(
		m_projectileBP, muzzleLoc, muzzleRot
		);//use get sockket loc?
	projectile->FireDirection(muzzleRot.Vector(), muzzleLoc);
	float FinalRecoil = FMath::FRandRange(-1.0f, -1.25f);
	AddControllerYawInput(FinalRecoil);

}

void ABSDPawn::PitchCamera(float Axis)
{
	AddControllerPitchInput(Axis * GetWorld()->GetDeltaSeconds() * 45);
}

void ABSDPawn::YawCamera(float Axis)
{
	AddControllerYawInput(Axis * GetWorld()->GetDeltaSeconds() * 45);
}



