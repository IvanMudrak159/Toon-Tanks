// Fill out your copyright notice in the Description page of Project Settings.
#include "Tower.h"
#include "Tank.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr) return;

	if (IsInRange() && Tank->bAlive == true)
	{
		Fire();
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
