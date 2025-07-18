// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamRelated.h"

void UTeamRelated::SetTeam_Implementation(int32 TeamNumber)
{
	Team = TeamNumber;
}

void UTeamRelated::GetTeam_Implementation(int32& TeamNumber)
{
	TeamNumber = Team;
}

void UTeamRelated::IsInSameTeam_Implementation(int32 InputTeam, bool& SameTame)
{
	SameTame = (Team == InputTeam);
}
