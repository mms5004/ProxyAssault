// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuildingInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UBuildingInterface : public UInterface
{
	GENERATED_BODY()
};

class IBuildingInterface
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	//void ProduceUnit();
};