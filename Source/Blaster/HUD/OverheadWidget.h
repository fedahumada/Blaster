// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class BLASTER_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetDisplayText(FString TextToDisplay);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* InPawn);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DisplayText;

protected:
	virtual void OnLevelRemovedFromWorld(ULevel* Inlevel, UWorld* InWorld) override;
};
