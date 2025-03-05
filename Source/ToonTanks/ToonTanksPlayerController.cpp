// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	UE_LOG(LogTemp, Warning, TEXT("Pawn SetPlayerEnabledState"));
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn is null"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Pawn found!"));
	if (bPlayerEnabled)
	{
		ControlledPawn->EnableInput(this);
	} else
	{
		ControlledPawn->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}

void AToonTanksPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AToonTanksGameMode* ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
	if (ToonTanksGameMode != nullptr)
	{
		ToonTanksGameMode->OnStartTimerFinish.AddDynamic(this, &AToonTanksPlayerController::HandleStartTimer);
	}
}

void AToonTanksPlayerController::HandleStartTimer()
{
	SetPlayerEnabledState(true);
}
