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
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>("DefaultSceneRoot");
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	/*static ConstructorHelpers::FObjectFinder<UStaticMesh>mysphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere'"));

	if (mysphere.Succeeded())
		Weapon->SetStaticMesh(mysphere.Object);

	Weapon->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));*/
	FVector currentLoc = GetActorLocation();
	currentLoc.Z -= 50;
	Weapon->SetWorldLocation(currentLoc);
	RootComponent = Weapon;
	CameraArm->SetupAttachment(Weapon);


	CameraArm->TargetArmLength = 30.0f;
	CameraArm->bEnableCameraLag = true;
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->CameraLagSpeed = 2.0f;


	MainCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	MainCamera->SetRelativeLocation(FVector(-50.0f, 0.0f, 0.0f));
	MainCamera->bUsePawnControlRotation = false;
	
}



void ABSDPawn::PreInitializeComponents()
{
	manager = new FWeaponManager(20);
	manager->Initialize(GetWorld());
}

void ABSDPawn::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	delete manager;
	manager = nullptr;
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

	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);
	// transform muzzleoffset from camera space to world space
	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(Offset);
	FRotator MuzzleRotation = CameraRotation;
	MuzzleRotation.Pitch += -5.0f;

	manager->Shoot(MuzzleRotation.Vector(), MuzzleLocation, MuzzleRotation);
	
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



