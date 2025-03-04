// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

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
