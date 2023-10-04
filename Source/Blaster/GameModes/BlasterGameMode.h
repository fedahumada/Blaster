// Copyright Fedahumada

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BlasterGameMode.generated.h"

class ABlasterCharacter;
class ABlasterPlayerController;
class ACharacter;
class AController;

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PlayerEliminated(ABlasterCharacter* ElimmedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController);

	virtual void RequestRespond(ACharacter* ElimmedCharacter, AController* ElimmedController);
};
