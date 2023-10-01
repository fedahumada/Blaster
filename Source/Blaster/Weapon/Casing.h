// Copyright Fedahumada

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casing.generated.h"

class USoundCue;

UCLASS()
class BLASTER_API ACasing : public AActor
{
	GENERATED_BODY()
	
public:	
	ACasing();

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void BeginPlay() override;

private:	
	float DestroyDelay = 0.35f;

	FTimerHandle DestroyTimer;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CasingMesh;

	UPROPERTY(EditAnywhere)
	float BulletShellEjectionImpulse;

	UPROPERTY(EditAnywhere)
	USoundCue* BulletShellSound;

	void StartDestroyTimer();

	void DestroyTimerFinished();

};
