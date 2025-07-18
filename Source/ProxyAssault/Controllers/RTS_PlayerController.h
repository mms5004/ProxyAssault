// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputInterface.h"
#include "EnhancedInputSubsystems.h"
#include "RTS_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROXYASSAULT_API ARTS_PlayerController : public APlayerController, public IControllerInputInterface
{
	GENERATED_BODY()
	
public:
    //ARTS_PlayerController();

	UFUNCTION(BlueprintCallable)
	void PossessPawn(APawn* NewPawn);
protected:
	virtual void BeginPlay() override; //Too early to reference the player (didn't spawn and possess yet)
	virtual void SetupInputComponent() override; //called by InitInputSystem() wich setup mouse
	virtual void OnPossess(APawn* aPawn) override; //Called after the player spawn

	UPROPERTY(BlueprintReadWrite)
	APawn* DefaultPossessedActor;
	TScriptInterface<IControllerInputInterface> PossessedInterface;

	UFUNCTION(BlueprintImplementableEvent)
	void PauseMenu();


#pragma region Input
	// https://dev.epicgames.com/documentation/en-us/unreal-engine/enhanced-input-in-unreal-engine Used
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MovementAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ControlAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LeftClickAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* RightClickAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* PauseAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ShiftAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ZoomAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* PlayUnitAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* EscapeAction;
#pragma endregion Input
		

private:
	void DispatchInput(const FInputActionInstance& Instance);
};
