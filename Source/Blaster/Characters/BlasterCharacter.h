// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "Blaster/Interfaces/InteractWithCrosshairsInterface.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
#include "BlasterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
class UCombatComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;
class AWeapon;
class ABlasterPlayerController;
class USoundCue;

UCLASS()
class BLASTER_API ABlasterCharacter : 
	public ACharacter, 
	public IInteractWithCrosshairsInterface
{
	GENERATED_BODY()

public:
	ABlasterCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;

	virtual void OnRep_ReplicatedMovement() override;
	
	void PlayFireMontage(bool bAiming);

	void PlayEliminationMontage();

	void Elimination();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastEliminated();

	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

	void Movement(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void EquipButtonPressed();

	virtual void Jump() override;

	void CrouchButtonPressed();

	void AimButtonPressed(const FInputActionValue& Value);

	void AimOffset(float DeltaTime);

	void CalculateAO_Pitch();

	void SimProxiesTurn();

	void FireButtonPressed(const FInputActionValue& Value);

	void PlayHitReactMontage();
	
	void UpdateHUDHealth();

	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController,AActor* DamageCauser);

	//
	//Input Actions & Context
	//
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputMappingContext* CharacterMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputAction* FireAction;

	//
	//Animation montages
	//
	
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* FireRifleMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* EliminationMontage;

private:	
	float AO_Yaw;

	float InterpAO_Yaw;

	float AO_Pitch;

	bool bRotateRootBone;

	float TurnThreshold = 0.5f;

	float ProxyYaw;

	float TimeSinceLastMovementReplication;

	FRotator ProxyRotationLastFrame;

	FRotator ProxyRotation;

	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace;
	
	float CalculateSpeed();

	void HideCameraIfCharacterClose();

	void TurnInPlace(float DeltaTime);

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	AWeapon* OverlappingWeapon;

	UPROPERTY(VisibleAnywhere)
	UCombatComponent* CombatComp;

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;

	//
	// Player health - Elimination & Respawn
	//
	ABlasterPlayerController* BlasterPlayerController;

	bool bEliminated = false;

	FTimerHandle ElimTimer;

	void ElimTimerFinished();
	
	UPROPERTY(EditDefaultsOnly)
	float ElimDelay = 3.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere, Category = "Player Stats")
	float Health = 100.f;

	UFUNCTION()
	void OnRep_Health();

	//
	//Dissolve Effect
	//

	UFUNCTION()
	void UpdateDissolveMaterial(float DissolveValue);

	void StartDissolve();

	FOnTimelineFloat DissolveTrack;

	UPROPERTY(VisibleAnywhere, Category = Elimination)
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, Category = Elimination)
	UMaterialInstance* DissolveMaterialInstance;

	UPROPERTY(EditAnywhere)
	UCurveFloat* DissolveCurve;

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DissolveTimeline;

	//
	//Elimination Bot
	//

	UPROPERTY(EditAnywhere)
	UParticleSystem* ElimBotEffect;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ElimBotComponent;

	UPROPERTY(EditAnywhere)
	USoundCue* ElimBotSound;

public:
	void SetOverlappinWeapon(AWeapon* Weapon);

	AWeapon* GetEquippedWeapon();
	
	FVector GetHitTarget() const;

	bool IsWeaponEquipped();

	bool IsAiming();

	FORCEINLINE bool IsEliminated() const { return bEliminated; }

	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }

	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }

	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }

	FORCEINLINE float GetHealth() const { return Health; }

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
};
