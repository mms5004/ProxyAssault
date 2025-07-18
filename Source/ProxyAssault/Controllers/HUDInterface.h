// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HUDInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UHUDInterface : public UInterface
{
	GENERATED_BODY()
};

class IHUDInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Selection")
	void PlayerMarquee(bool Pressed, APlayerController* Controller);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Selection")
	void Execute_PlayUnitSelected();
};