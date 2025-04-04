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
	else if (ABaseEnemy* DestroyedEnemy = Cast<ABaseEnemy>(DeadActor))
	{
		TargetEnemies--;
		DestroyedEnemy->HandleDestruction();
		if (TargetEnemies <= 0)
		{
			GameOver(true);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Enemies: %d"), TargetEnemies);
}

void AToonTanksGameMode::BeginPlay()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("GameMode running as Listen Server"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("GameMode running as Client"));
	}

	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	TargetEnemies = GetTargetEnemiesCount();
	HandleGameStart();
}

int32 AToonTanksGameMode::GetTargetEnemiesCount()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this, ABaseEnemy::StaticClass(), Enemies);
	return Enemies.Num();
}

void AToonTanksGameMode::HandleGameStart()
{
	StartGame();
	int32 NumPlayers = GetNumPlayers();
	UE_LOG(LogTemp, Log, TEXT("Current number of players: %d"), NumPlayers);
	if (TankPlayerController)
	{
		TankPlayerController->SetPlayerEnabledState(false);
		FTimerDelegate OnGameStart = FTimerDelegate::CreateLambda([this]()
			{
			OnStartTimerFinish.Broadcast();
			});
		GetWorldTimerManager().SetTimer(TimerHandle, OnGameStart, StartDelay, false);
	}
} 