// Fill out your copyright notice in the Description page of Project Settings.


#include "InputInterface.h"

void IControllerInputInterface::ChangeInputState_Implementation(bool Enable)
{
	InputState = Enable;
	UObject* Obj = _getUObject();
	if (!Obj) { return; }
	if (InputState)
	{
		IControllerInputInterface::Execute_InputEnable(Obj);
	}
	else 
	{
		IControllerInputInterface::Execute_DisableEnable(Obj);
	}
}