// Copyright Fedahumada

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

class ABlasterHUD;
class UCharacterOverlay;
class ABlasterGameMode;

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetHUDHealth(float Health, float MaxHealth);

	void SetHUDScore(float Score);

	void SetHUDDefeats(int32 Defeats);

	void SetHUDWeaponAmmo(int32 Ammo);

	void SetHUDCarriedAmmo(int32 Ammo);

	void SetHUDMatchCountdown(float CountdownTime);

	void SetHUDAnnouncementCountdown(float CountdownTime);

	virtual void OnPossess(APawn* InPawn) override;

	virtual float GetServerTime(); //Client-Server synced successful

	virtual void ReceivedPlayer() override; // Synced with Server clock asap

	void OnMatchStateSet(FName State);

protected:
	virtual void BeginPlay() override;

	void SetHUDTime();

	void PollInit();

	void HandleMatchStarted();

	void HandleCooldown();


	//Sync between client and server
	void CheckTimeSync(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);

	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);

	float ClientServerDelta = 0.f; //Diference between client and server time

	float TimeSyncRunningTime = 0.f;
	
	UPROPERTY(EditAnywhere, Category = TimeSync)
	float TimeSyncFrequency = 5.f;

	UFUNCTION(Server, Reliable)
	void ServerCheckMatchState();

	UFUNCTION(Client, Reliable)
	void ClientJoinMidgame(FName StateOfMatch, float Warmup, float Match, float Cooldown, float StartingTime);

private:
	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY()
	ABlasterHUD* BlasterHUD;
	
	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;

	UPROPERTY()
	ABlasterGameMode* BlasterGameMode;

	
	//Initialize match timers
	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	FName MatchState;

	float LevelStartingTime = 0.f;

	float MatchTime = 0.f;

	float WarmupTime = 0.f;

	float CooldownTime = 0.f;

	uint32 CountdownInt = 0;


	//In case overlay doesn't initialize correctly, cache important values
	bool bInitializeCharacterOverlay = false;

	float HUDHealth;

	float HUDMaxHealth;

	float HUDScore;

	int32 HUDDefeats;

};
