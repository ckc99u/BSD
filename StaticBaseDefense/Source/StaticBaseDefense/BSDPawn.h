// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "StaticBaseDefense/WeaponManager.h"
#include "GameFramework/Pawn.h"
#include "BSDPawn.generated.h"


UCLASS()
class STATICBASEDEFENSE_API ABSDPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABSDPawn();


public:

	virtual void PreInitializeComponents() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
		void Fire();
	UFUNCTION()
		void PitchCamera(float Axis);
	UFUNCTION()
		void YawCamera(float Axis);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Offset = FVector(-50.0f, -20.0f, 0.0f);
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Weapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent *CameraArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* MainCamera;


	UPROPERTY()
		FRotator CamerRotator;

	FWeaponManager *manager;
	FVector _dir;
};
