// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ABaseEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (IsInRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

bool ABaseEnemy::IsInRange() const
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		return Distance <= FireRange;
	}
	return false;
}
