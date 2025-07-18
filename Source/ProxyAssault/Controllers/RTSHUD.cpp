// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"
#include "TimerManager.h"
//#include "Kismet/GameplayStatics.h" APlayerController* test = UGameplayStatics::GetPlayerController(GetWorld(), 0);


void ARTSHUD::PlayerMarquee_Implementation(bool Pressed, APlayerController* Controller)
{
	if (Pressed) 
	{
		CallingController = Controller;
		CallingController->GetMousePosition(StartMousePosition.X, StartMousePosition.Y);
		BuildingCheck();
		if (!SelectedBuilding)
		{
			GetWorld()->GetTimerManager().SetTimer(UpdateCursorHandle, this, &ARTSHUD::UpdateCursor, 0.01f, true);
		}
	}
	else 
	{
		UpdateCursorHandle.Invalidate();
	}
	IsDrawing = Pressed;
}

void ARTSHUD::DrawHUD()
{
	if (IsDrawing)
	{
		DrawRect(Color, StartMousePosition.X, StartMousePosition.Y,
			CurrentMousePosition.X-StartMousePosition.X, CurrentMousePosition.Y - StartMousePosition.Y);
		//Need to refactor by filtering by interface on the AActorList (and avoid a hard reference to generic unit class)
		//GetActorsInSelectionRectangle(UnitType, StartMousePosition, CurrentMousePosition, ActorInRectangle, false, false);
		SelectUnitInBlueprint();
	}
}

void ARTSHUD::UpdateCursor()
{
	CallingController->GetMousePosition(CurrentMousePosition.X, CurrentMousePosition.Y);
}