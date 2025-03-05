// Fill out your copyright notice in the Description page of Project Settings.
#include "Tower.h"
#include "Tank.h"
#include "TimerManager.h"

bool ATower::CheckFireCondition()
{
	if (!Super::CheckFireCondition()) return false;

	if (Tank == nullptr) return false;

	if (IsInRange() && Tank->bAlive == true)
	{
		Fire();
		return true;
	}
	return false;
}