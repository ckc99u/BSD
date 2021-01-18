// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "StaticBaseDefense/PlayerBase.h"
#include "DefensePlayerController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBaseDelegate);
UCLASS()
class STATICBASEDEFENSE_API ADefensePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADefensePlayerController();
	~ADefensePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
private:
	UFUNCTION()
	void timerCounter();//spawn increase by time
public:
	UPROPERTY(EditAnywhere)
	int health = 100;
	UPROPERTY(EditAnywhere)
	int Timer = 0;

	FBaseDelegate IsDeath;

	UPROPERTY(BlueprintReadOnly)
		FText canvasTime;
	UPROPERTY(BlueprintReadOnly)
	FText canvasHealth;
	UPROPERTY(BlueprintReadOnly)
		APlayerBase *Base;

	FTimerHandle  InOutHandle;

};
