// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemy.h"

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	//TODO: try to make handle subscription without casting
	AToonTanksGameMode* ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
	if (ToonTanksGameMode != nullptr)
	{
		ToonTanksGameMode->OnStartTimerFinish.AddDynamic(this, &ABaseEnemy::HandleGameTimerStart);
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseEnemy::Reload, FireRate, true);

}

void ABaseEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (IsInRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ABaseEnemy::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
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

void ABaseEnemy::HandleGameTimerStart()
{
	bGameStarted = true;
}

//TODO: seems very strange, rename somehow
void ABaseEnemy::Reload()
{
	CheckFireCondition();
}

bool ABaseEnemy::CheckFireCondition()
{
	return bGameStarted;
}
