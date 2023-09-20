// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BlasterAnimInstance.generated.h"

class ABlasterCharacter;

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
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Character)
	ABlasterCharacter* BlasterCharacter;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	float Speed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Movement)
	bool bIsAccelerating;
};
