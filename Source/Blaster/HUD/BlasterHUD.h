// Copyright Fedahumada

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlasterHUD.generated.h"

class UTexture2D;
class UCharacterOverlay;
class UUserWidget;
class UAnnouncement;

USTRUCT(BlueprintType)
struct FHUDPackage {
	GENERATED_BODY()

public:
	UTexture2D* CrosshairsCenter;
	UTexture2D* CrosshairsLeft;
	UTexture2D* CrosshairsRight;
	UTexture2D* CrosshairsTop;
	UTexture2D* CrosshairsBottom;
	FLinearColor CrosshairsColor;
	float CrosshairsSpread;
};

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;


	//Main HUD overlay
	void AddCharacterOverlay();
	
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<UUserWidget> CharacterOverlayClass;

	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;


	//Announcement overlay
	void AddAnnouncement();

	UPROPERTY(EditAnywhere, Category = "Announcements")
	TSubclassOf<UUserWidget> AnnouncementClass;

	UPROPERTY()
	UAnnouncement* Announcement;

protected:
	virtual void BeginPlay() override;

private:
	FHUDPackage HUDPackage;

	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread, FLinearColor CrosshairsColor);

	UPROPERTY(EditAnywhere)
	float CrosshairsSpreadMax = 16.f;
public:
	FORCEINLINE void SetHUDPackage(const FHUDPackage& Package) { HUDPackage = Package; }
};
