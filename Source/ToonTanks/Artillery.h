// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "Artillery.generated.h"

class ADecalActor;

UCLASS()
class TOONTANKS_API AArtillery : public ABaseEnemy
{
	GENERATED_BODY()

public:
	AArtillery();
	virtual void Tick(float DeltaSeconds) override;

protected:
	void BeginPlay() override;
	bool CheckFireCondition() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	UMaterial* DecalMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float angle = 45;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float fireForceOffset = 70;
	ADecalActor* SpawnDecal(const FVector& TankLocation) const;
};
