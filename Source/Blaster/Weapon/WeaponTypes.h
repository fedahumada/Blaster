#pragma once

#define TRACE_LENGTH 80000.f

UENUM(BlueprintType)
enum class EWeaponType : uint8 {
	EWT_AssaultRifle UMETA(Display = "Assault Rifle"),
	EWT_RocketLauncher UMETA(Display = "Rocket Launcher"),
	EWT_Pistol UMETA(Display = "Pistol"),
	EWT_SubMachineGun UMETA(Display = "SubMachine Gun"),
	EWT_Shotgun UMETA(Display = "Shotgun"),
	EWT_SniperRifle UMETA(Display = "SniperRifle"),

	EWT_MAX UMETA(Display = "DefaultMAX"),
};