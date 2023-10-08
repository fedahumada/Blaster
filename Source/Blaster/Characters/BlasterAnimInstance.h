// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "Animation/AnimInstance.h"
#include "BlasterAnimInstance.generated.h"

class ABlasterCharacter;
class AWeapon;

/**
 * 
 */
UCLASS()
class BLASTER_API UBlasterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	FRotator CharacterRotationLastFrame;

	FRotator CharacterRotation;

	AWeapon* EquippedWeapon;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Character)
	ABlasterCharacter* BlasterCharacter;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	float Speed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	bool bIsAccelerating;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	bool bWeaponEquipped;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	bool bIsCrouched;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	bool bIsAiming;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	float YawOffset;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	float Lean;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	float AOYaw;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	float AOPitch;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	FTransform LeftHandTransform;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	FRotator RightHandRotation;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	bool bIsLocallyControlled;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Character)
	ETurningInPlace TurningInPlace;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Character)
	bool bRotateRootBone;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Character)
	bool bEliminated;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Character)
	bool bUseFABRIK;
};
