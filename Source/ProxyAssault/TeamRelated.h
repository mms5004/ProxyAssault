// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProxyAssault/SelectionInterface.h"
#include "TeamRelated.generated.h"  

UCLASS()
class PROXYASSAULT_API UTeamRelated : public UObject, public ISelectionInterface
{
	GENERATED_BODY()

protected:
	virtual void SetTeam_Implementation(int32 TeamNumber) override;
	virtual void GetTeam_Implementation(int32& TeamNumber) override;
	virtual void IsInSameTeam_Implementation(int32 InputTeam, bool& SameTame) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	int Team = 0;
};
