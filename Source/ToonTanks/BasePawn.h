// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"


class AProjectile;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	virtual void HandleDestruction();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString logString;

protected:
	void RotateTurret(FVector LookAtTarget, bool drawDebug = false);

	UFUNCTION(BlueprintCallable)

	virtual void Fire(FVector velocity);
	virtual void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UFUNCTION()
	virtual void OnProjectileHitCallback(AProjectile* HitProjectile);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	USoundBase* DeathSound;


	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;
};
