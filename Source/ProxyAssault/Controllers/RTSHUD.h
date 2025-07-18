// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDInterface.h"
#include "RTSHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROXYASSAULT_API ARTSHUD : public AHUD, public IHUDInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Selection")
	bool IsDrawing;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Selection")
	FVector2D StartMousePosition;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Selection")
	FVector2D CurrentMousePosition;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	FLinearColor Color;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Selection", meta = (MultiLine = "true"))
	TArray<AActor*> SelectedUnit;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Selection", meta = (MultiLine = "true"))
	TSubclassOf<class AActor> UnitType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Selection")
	TArray<AActor*> ActorInRectangle;

protected:
	UFUNCTION()
	void PlayerMarquee_Implementation(bool Pressed, APlayerController* Controller) override;
	UFUNCTION()
	void DrawHUD() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SelectUnitInBlueprint();

	UFUNCTION(BlueprintImplementableEvent)
	void BuildingCheck();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Selection")
	AActor* SelectedBuilding;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Selection")
	FTimerHandle UpdateCursorHandle;
	UFUNCTION()
	void UpdateCursor();
	UPROPERTY()
	APlayerController* CallingController;
};