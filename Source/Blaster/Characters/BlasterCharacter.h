// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "Blaster/BlasterTypes/CombatState.h"
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
class ABlasterPlayerState;
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


	//Input
	void FireButtonPressed(const FInputActionValue& Value);

	//Montages
	void PlayFireMontage(bool bAiming);

	void PlayReloadMontage();

	void PlayEliminationMontage();

	void PlayHitReactMontage();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowSniperScopeWidget(bool bShowScope);
	
	//Elimination
	void Elimination();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastEliminated();

	virtual void Destroyed() override;

	//Disable Gameplay 
	UPROPERTY(Replicated)
	bool bDisableGameplay = false;

protected:
	virtual void BeginPlay() override;

	void AddMappingContextToCharacter();


	//Initialize HUD
	void PollInit();
	

	//Input Actions
	void Movement(const FInputActionValue& Value);
	
	virtual void Jump() override;
	
	void CrouchButtonPressed();
	
	void EquipButtonPressed();
	
	void ReloadButtonPressed();
	
	void Look(const FInputActionValue& Value);
	
	void AimButtonPressed(const FInputActionValue& Value);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	UInputAction* ReloadAction;


	//Animation montages
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* FireRifleMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* EliminationMontage;


	//AimOffset & turning
	void AimOffset(float DeltaTime);

	void CalculateAO_Pitch();

	void SimProxiesTurn();

	void RotateInPlace(float DeltaTime);


	//Health
	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController,AActor* DamageCauser);

	void UpdateHUDHealth();

private:	
	//Basic & other components
	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* OverheadWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCombatComponent* CombatComp;


	//AimOffset & movement
	float CalculateSpeed();

	void HideCameraIfCharacterClose();

	void TurnInPlace(float DeltaTime);

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


	//Equip weapon
	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	AWeapon* OverlappingWeapon;


	// Player health - Elimination & Respawn
	UFUNCTION()
	void OnRep_Health();

	bool bEliminated = false;

	FTimerHandle ElimTimer;

	UPROPERTY()
	ABlasterPlayerState* BlasterPlayerState;

	UPROPERTY()
	ABlasterPlayerController* BlasterPlayerController;
	void ElimTimerFinished();
	
	UPROPERTY(EditDefaultsOnly)
	float ElimDelay = 3.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere, Category = "Player Stats")
	float Health = 100.f;

	//Dissolve Effect
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

	//Elimination Bot

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

	ECombatState GetCombatstate() const;
	
	FORCEINLINE bool IsEliminated() const { return bEliminated; }

	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }

	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }

	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }

	FORCEINLINE float GetHealth() const { return Health; }

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	FORCEINLINE UCombatComponent* GetCombatComp() const { return CombatComp; }

	FORCEINLINE bool GetDisableGameplay() const { return bDisableGameplay; }
};
