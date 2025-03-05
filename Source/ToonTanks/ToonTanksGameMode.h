// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartTimerFinish);

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor *DeadActor);
	FOnStartTimerFinish OnStartTimerFinish;

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bGameWon);

private:
	class ATank* Tank;
	class AToonTanksPlayerController* TankPlayerController;

	FTimerHandle TimerHandle;
	float StartDelay = 3.f;

	int32 TargetEnemies = 0;
	int32 GetTargetEnemiesCount();

	void HandleGameStart();
};
