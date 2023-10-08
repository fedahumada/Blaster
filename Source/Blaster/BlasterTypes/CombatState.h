#pragma once
UENUM(BlueprintType)
enum class ECombatState : uint8 {
	ECS_Unnocupied UMETA(Display = "Unnocupied"),
	ECS_Reloading UMETA(Display = "Reloading"),

	ECS_MAX UMETA(Display = "DefaultMAX"),
};