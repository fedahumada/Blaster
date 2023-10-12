// Copyright Fedahumada

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BlasterGameMode.generated.h"

class ABlasterCharacter;
class ABlasterPlayerController;
class ACharacter;
class AController;

namespace MatchState {
	extern BLASTER_API const FName Cooldown; // Match duration has been reached. Display winner and begin cooldown timer
}

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ABlasterGameMode();

	virtual void Tick(float DeltaTime);

	virtual void PlayerEliminated(ABlasterCharacter* ElimmedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController);

	virtual void RequestRespond(ACharacter* ElimmedCharacter, AController* ElimmedController);

	float LevelStartingTime = 0.f;
	
	UPROPERTY(EditDefaultsOnly)
	float WarmupTime = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float MatchTime = 120.f;

	UPROPERTY(EditDefaultsOnly)
	float CooldownTime = 10.f;

protected:
	virtual void BeginPlay() override;

	virtual void OnMatchStateSet() override;

private:
	float CountdownTime = 0.f;

public:
	FORCEINLINE float GetCountdownTime() const{ return CountdownTime; }
	FORCEINLINE float GetLevelStartingTime() const { return LevelStartingTime; }
};
