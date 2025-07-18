// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void ARTS_PlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(MappingContext, 0);
    }
}

void ARTS_PlayerController::OnPossess(APawn* aPawn)
{    
    Super::OnPossess(aPawn);
    if (!DefaultPossessedActor)
    {
        DefaultPossessedActor = this->AcknowledgedPawn;
        PossessPawn(nullptr);
    }
}

void ARTS_PlayerController::PossessPawn(APawn* NewPawn)
{
    if (PossessedInterface.GetObject() == NewPawn && NewPawn)
    {
        return;
    }
    if (PossessedInterface) 
    {
        PossessedInterface->ChangeInputState_Implementation(false);
    }

    //Select default actor interface if NewPawn null
    if (!NewPawn) 
    {
        PossessedInterface = TScriptInterface<IControllerInputInterface>(DefaultPossessedActor);
    }
    else 
    {
        if (NewPawn->Implements<UControllerInputInterface>()) 
        {
            PossessedInterface = TScriptInterface<IControllerInputInterface>(NewPawn);
        }
    }

    //Print an error log
    ensureAlways(PossessedInterface); 
    if (PossessedInterface)
    {
        PossessedInterface->ChangeInputState_Implementation(true);
    }
}


//Inputs part
void ARTS_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
    {
        Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARTS_PlayerController::DispatchInput);
        Input->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ARTS_PlayerController::DispatchInput);
        Input->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ARTS_PlayerController::DispatchInput);
        Input->BindAction(MovementAction, ETriggerEvent::Completed, this, &ARTS_PlayerController::DispatchInput); //To reset velocity
        Input->BindAction(PlayUnitAction, ETriggerEvent::Started, this, &ARTS_PlayerController::DispatchInput);
        Input->BindAction(EscapeAction, ETriggerEvent::Started, this, &ARTS_PlayerController::PauseMenu);
        
        //Toggle inputs
        Input->BindAction(LeftClickAction, ETriggerEvent::Started, this, &ARTS_PlayerController::DispatchInput);
        Input->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &ARTS_PlayerController::DispatchInput);
        Input->BindAction(RightClickAction, ETriggerEvent::Started, this, &ARTS_PlayerController::DispatchInput);
        Input->BindAction(RightClickAction, ETriggerEvent::Completed, this, &ARTS_PlayerController::DispatchInput);
        Input->BindAction(ShiftAction, ETriggerEvent::Started, this, &ARTS_PlayerController::DispatchInput);
        Input->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ARTS_PlayerController::DispatchInput);
        Input->BindAction(ControlAction, ETriggerEvent::Started, this, &ARTS_PlayerController::DispatchInput);
        Input->BindAction(ControlAction, ETriggerEvent::Completed, this, &ARTS_PlayerController::DispatchInput);
        
        Input->BindAction(PauseAction, ETriggerEvent::Started, this, &ARTS_PlayerController::DispatchInput);
    }    
}


void ARTS_PlayerController::DispatchInput(const FInputActionInstance& Instance)
{
    if (!PossessedInterface) { return; }
    auto action = Instance.GetSourceAction();
    UObject* pawn = PossessedInterface.GetObject();

    if (action == LookAction)
    {
        IControllerInputInterface::Execute_Look(pawn, Instance.GetValue().Get<FVector2D>());
    }
    else if (action == MovementAction)
    {
        IControllerInputInterface::Execute_Movement(pawn, Instance.GetValue().Get<FVector2D>());
    }
    else if (action == ControlAction)
    {
        IControllerInputInterface::Execute_Control(pawn, Instance.GetValue().Get<bool>());
    }
    else if (action == LeftClickAction)
    {
        IControllerInputInterface::Execute_LeftClick(pawn, Instance.GetValue().Get<bool>());
    }
    else if (action == RightClickAction)
    {
        IControllerInputInterface::Execute_RightClick(pawn, Instance.GetValue().Get<bool>());
    }
    //else if (action == PauseAction)
    //{
    //    IControllerInputInterface::Execute_Escape(pawn);
    //}
    else if (action == ShiftAction)
    {
        IControllerInputInterface::Execute_Shift(pawn, Instance.GetValue().Get<bool>());
    }
    else if (action == ZoomAction)
    {
        IControllerInputInterface::Execute_Zoom(pawn, Instance.GetValue().Get<float>());
    }
    else if (action == PlayUnitAction) 
    {
        IControllerInputInterface::Execute_PlayUnit(pawn);
    }
}