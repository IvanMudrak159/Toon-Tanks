// Fill out your copyright notice in the Description page of Project Settings.


#include "Artillery.h"

#include "Components/DecalComponent.h"
#include "Engine/DecalActor.h"

AArtillery::AArtillery()
{
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(TurretMesh);
	ProjectileSpawnPoint->SetupAttachment(GunMesh);
}

void AArtillery::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AArtillery::CheckFireCondition()
{
	if (!Super::CheckFireCondition()) return false;

	if (!Tank or !IsInRange())
	{
		return false;
	}
	if (!Tank->bAlive)
	{
		return false;
	}

	FVector TankLocation = Tank->GetActorLocation();
	float Distance = FVector::Dist(GetActorLocation(), TankLocation);
	float sinValue = sin(FMath::DegreesToRadians(2 * angle));
	float gravity = FMath::Abs(GetWorld()->GetGravityZ());
	float initialVelocity = sqrt(Distance * gravity / sinValue) - fireForceOffset;
	ADecalActor* SpawnedDecal = SpawnDecal(TankLocation);
	Fire(GunMesh->GetForwardVector() * initialVelocity, SpawnedDecal);
	return true;
}

//TODO definitely should not be here
ADecalActor* AArtillery::SpawnDecal(const FVector& TankLocation) const
{
	if (!Tank)
	{
		return nullptr;
	}
	FVector StartLocation = TankLocation;
	FVector EndLocation = StartLocation - FVector(0,0,100);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Tank);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
	{
		FVector DecalLocation = HitResult.ImpactPoint;
		DecalLocation.Z = 0;

		FRotator DecalRotation = HitResult.ImpactNormal.Rotation();
		ADecalActor* Decal = GetWorld()->SpawnActor<ADecalActor>(DecalLocation, DecalRotation);
		Decal->SetActorRotation(DecalRotation);
		if (Decal)
		{
			UDecalComponent* DecalComp = Decal->GetDecal();
			if (DecalComp)
			{
				DecalComp->SetDecalMaterial(DecalMaterial);
				DecalComp->DecalSize = FVector(60, 120, 120);
				Decal->SetRootComponent(DecalComp);
			}
			return Decal;
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 5.0f, 0, 2.0f);
	}
	return nullptr;
}

