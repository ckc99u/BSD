// Fill out your copyright notice in the Description page of Project Settings.


#include "DefensePlayerController.h"

ADefensePlayerController::ADefensePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

}
ADefensePlayerController::~ADefensePlayerController(){}



void ADefensePlayerController::BeginPlay()
{
	canvasHealth = FText::FromString(FString::FromInt(health));
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector playerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	playerPos.Z -= 100;
	Base = GetWorld()->SpawnActor<APlayerBase>(playerPos, FRotator(0,0,0),SpawnInfo );
	GetWorld()->GetTimerManager().SetTimer(InOutHandle, this, &ADefensePlayerController::timerCounter, 1.0, true, 0);
}


void ADefensePlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Base->Destroy();
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void ADefensePlayerController::timerCounter()
{
	 canvasTime = FText::FromString( FString::FromInt(++Timer));
}
float  ADefensePlayerController::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "to player Damage");
	health -= DamageAmount;
	canvasHealth = FText::FromString(FString::FromInt(health));
	if (health <= 0) 
	{
		IsDeath.Broadcast();
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
	return health;

}


