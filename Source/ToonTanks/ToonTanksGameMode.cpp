// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s died for our sins."), *GetNameSafe(DeadActor));
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (TankPlayerController)
		{
			TankPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		TargetTowers--;
		DestroyedTower->HandleDestruction();
		if (TargetTowers <= 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	TargetTowers = GetTargetTowersCount();
	HandleGameStart();
}

int32 AToonTanksGameMode::GetTargetTowersCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}

void AToonTanksGameMode::HandleGameStart()
{
	StartGame();
	if (TankPlayerController)
	{
		TankPlayerController->SetPlayerEnabledState(false);
		UE_LOG(LogTemp, Warning, TEXT("Timer Started"));
		FTimerDelegate OnGameStart = FTimerDelegate::CreateUObject(TankPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(TimerHandle, OnGameStart, StartDelay, false);
	}
} 