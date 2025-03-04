// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.h"
#include "BaseEnemy.generated.h"

UCLASS(Abstract)
class TOONTANKS_API ABaseEnemy : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	FTimerHandle TimerHandle;

	virtual void BeginPlay() override;
	bool IsInRange() const;

	ATank* Tank;
	float FireRate = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float FireRange = 15.f;
};
