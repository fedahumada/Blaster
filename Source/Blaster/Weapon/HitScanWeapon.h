// Copyright Fedahumada

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "HitScanWeapon.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AHitScanWeapon : public AWeapon
{
	GENERATED_BODY()
public:
	virtual void Fire(const FVector& HitTarget);

protected:
	FVector TraceEndWithScatter(const FVector& TraceStart, const FVector& HitTarget);

	void WeaponTraceHit(const FVector& TraceStart, const FVector& HitTarget, FHitResult& OutHit);

	UPROPERTY(EditAnywhere, Category = Weapon)
	class UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, Category = Weapon)
	USoundCue* HitSound;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float Damage = 10.f;

private:
	UPROPERTY(EditAnywhere, Category = Weapon)
	UParticleSystem* BeamParticles;

	UPROPERTY(EditAnywhere, Category = Weapon)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = Weapon)
	USoundCue* FireSound;


	//Trace end with scatter
	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	float DistanceToSphere = 800.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	float SphereRadius = 75.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	bool bUseScatter = false;
};
