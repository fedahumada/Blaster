// Copyright Fedahumada

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blaster/HUD/BlasterHUD.h"
#include "Blaster/Weapon/WeaponTypes.h"
#include "Blaster/BlasterTypes/CombatState.h"
#include "CombatComponent.generated.h"

class AWeapon;
class ABlasterCharacter;
class ABlasterPlayerController;
class ABlasterHUD;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	friend class ABlasterCharacter;

	UCombatComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
	void EquipWeapon(AWeapon* WeaponToEquip);

	void Reload();

	UFUNCTION(BlueprintCallable)
	void FinishReloading();

protected:
	virtual void BeginPlay() override;

	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	void SetHUDCrosshairs(float DeltaTime);

	void SetAiming(bool bAiming);

	void SetFiring(bool bFiring);

	void Fire();

	UFUNCTION()
	void OnRep_EquippedWeapon();

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetFiring(const FVector_NetQuantize& TraceHitTarget);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastFire(const FVector_NetQuantize& TraceHitTarget);

	UFUNCTION(Server, Reliable)
	void ServerReload();

	void HandleReload();

	int32 AmountToReload();
		
private:
	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed;

	UPROPERTY(EditAnywhere)
	float AimWalkSpeed;

	UPROPERTY()
	ABlasterCharacter* Character;

	UPROPERTY()
	ABlasterPlayerController* Controller;

	UPROPERTY()
	ABlasterHUD* HUD;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	AWeapon* EquippedWeapon;


	//
	//Combat State
	//
	UFUNCTION()
	void OnRep_CombatState();

	UPROPERTY(ReplicatedUsing = OnRep_CombatState)
	ECombatState CombatState = ECombatState::ECS_Unnocupied;


	//
	//HUD and Crosshairs
	//
	FHUDPackage HUDPackage;

	float CrosshairsVelocityFactor;

	float CrosshairsInAirVelocityFactor;

	float CrosshairsAimFactor;

	float CrosshairsShootingFactor;

	FVector HitTarget;


	//Aiming and FOV
	//	 FOV when not aiming, base camera FOV
	//
	float DefaultFOV;

	float CurrentFOV;

	UPROPERTY(Replicated)
	bool bIsAiming;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ZoomedFOV = 30.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ZoomedInterpSpeed = 20.f;

	void InterpFOV(float DeltaTime);


	//
	//Firing
	//

	bool CanFire();

	bool bCanFire = true;

	UPROPERTY(EditAnywhere)
	bool bIsFiring;

	//Automatic fire
	FTimerHandle FireTimer;
	
	void StartFireTimer();

	void FireTimerFinished();

	//
	//Ammo
	//
	void InitializeCarriedAmmo();

	UFUNCTION()
	void OnRep_CarriedAmmo();
	
	UPROPERTY(ReplicatedUsing = OnRep_CarriedAmmo)
	int32 CarriedAmmo; 

	TMap<EWeaponType, int32> CarriedAmmoMap;

	void UpdateAmmoValues();

	//Starting Ammo
	UPROPERTY(EditAnywhere)
	int32 StartingARAmmo = 30;

	UPROPERTY(EditAnywhere)
	int32 StartingRocketAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingPistolAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingSubMachineAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingShotgunAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingSniperAmmo = 0;

};
