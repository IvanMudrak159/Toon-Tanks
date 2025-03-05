// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "Tower.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABaseEnemy
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	bool CheckFireCondition() override;
};
