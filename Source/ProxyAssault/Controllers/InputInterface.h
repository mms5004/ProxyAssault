
//Based on UE5.6 documentation : https://dev.epicgames.com/documentation/en-us/unreal-engine/interfaces-in-unreal-engine
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UControllerInputInterface : public UInterface //UInputInterface already exists for HapticFeedback :/
{
	GENERATED_BODY()	
};

class IControllerInputInterface
{
	GENERATED_BODY()
public:
	//Allow the controller to notify unit switching by inputs
	//Only callable and dispatch event between InputEnable && DisableEnable
	void ChangeInputState_Implementation(bool Enable);
	//virtual void ChangeInputState_Implementation(bool Enable) final;
	bool IsInputEnable() { return InputState; };


#pragma region Input
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void Look(FVector2D Direction);

	UFUNCTION(BlueprintCallable ,BlueprintNativeEvent ,Category = "Input")
	void Movement(FVector2D Direction);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void Control(bool Enabled);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void LeftClick(bool Enabled);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void RightClick(bool Enabled);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void Shift(bool Enabled);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void Zoom(float Enhanced);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void PlayUnit();

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	//void Escape();
#pragma endregion Input


private:
	bool InputState;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void InputEnable();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void DisableEnable();
};
