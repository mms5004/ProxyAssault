// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectionInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class USelectionInterface : public UInterface
{
	GENERATED_BODY()
};

class ISelectionInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Selection")
	void Select(bool Selected);

	UFUNCTION(BlueprintNativeEvent, Category = "Team")
	void SetTeam(int32 TeamNumber);

	UFUNCTION(BlueprintNativeEvent, Category = "Team")
	void GetTeam(int32& TeamNumber);

	UFUNCTION(BlueprintNativeEvent, Category = "Team")
	void IsInSameTeam(int32 InputTeam, bool& SameTame);
};