// Fill out your copyright notice in the Description page of Project Settings.
#include "CameraPawn.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/LocalPlayer.h"
#include "TimerManager.h"
#include "GameFramework/HUD.h"

//To do :
//get hud interface instance without input functions

// Sets default values
ACameraPawn::ACameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);
}

void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UWidgetBlueprintLibrary::SetFocusToGameViewport();

	FVector previousRotation = SpringArm->GetComponentRotation().Euler();
	FVector EulerRotation = FVector(previousRotation.X, Curve->FloatCurve.Eval(SpringArm->TargetArmLength / CameraHeightLimit.Y), previousRotation.Z);
	RootScene->SetWorldRotation(FQuat::MakeFromEuler(EulerRotation));
}
//Play one frame before Begin play
void ACameraPawn::InputEnable_Implementation()
{
	CenterMouse();
}

void ACameraPawn::LeftClick_Implementation(bool Enabled)
{
	if (!HUDInterfaceInstance) 
	{
		AActor* hud = PC->GetHUD();
		if (hud->Implements<UHUDInterface>())
		{
			HUDInterfaceInstance = TScriptInterface<IHUDInterface>(hud);
			goto markEvent;
		}
	}
	else 
	{
		markEvent:
		HUDInterfaceInstance->Execute_PlayerMarquee(HUDInterfaceInstance.GetObject(), Enabled, PC);
	}
}

void ACameraPawn::PlayUnit_Implementation()
{
	if (!HUDInterfaceInstance)
	{
		AActor* hud = PC->GetHUD();
		if (hud->Implements<UHUDInterface>())
		{
			HUDInterfaceInstance = TScriptInterface<IHUDInterface>(hud);
			goto markEvent2;
		}
	}
	else
	{
	markEvent2:
		HUDInterfaceInstance->Execute_PlayUnitSelected();
	}
}

void ACameraPawn::Movement_Implementation(FVector2D Direction)
{
	MovementVector = Direction;
}

void ACameraPawn::Zoom_Implementation(float Enhanced)
{
	//Change rotation
	if (IsShifting) 
	{
		RootScene->AddWorldRotation(FRotator::MakeFromEuler(FVector(0, 0,ScrollMultiplicator * Enhanced)));
	}
	//Change Speed
	else if(IsCtrl)
	{
		MovementSpeed = FMath::Max(MovementSpeed, 0);
		FString Debug = "Panning Movement Speed: " + FString::SanitizeFloat(MovementSpeed);
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Cyan, Debug, true);
		MovementSpeed += Enhanced * ScrollMultiplicator;
	}
	//Zoom
	else 
	{
		float newLength = (SpringArm->TargetArmLength - ZoomMultiplicator * Enhanced);
		newLength = FMath::Clamp(newLength, CameraHeightLimit.X, CameraHeightLimit.Y);
		SpringArm->TargetArmLength = newLength;

		FVector previousRotation = SpringArm->GetComponentRotation().Euler();
		FVector EulerRotation = FVector(previousRotation.X,Curve->FloatCurve.Eval(newLength / CameraHeightLimit.Y), previousRotation.Z);
		RootScene->SetWorldRotation(FQuat::MakeFromEuler(EulerRotation));
	}
}

void ACameraPawn::Control_Implementation(bool Enabled)
{IsCtrl = Enabled;}

void ACameraPawn::Shift_Implementation(bool Enabled)
{IsShifting = Enabled;}

void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(CameraPan() * MovementSpeed, 1, false);
	HeightCheck(DeltaTime);
}

FVector ACameraPawn::CameraPan()
{
	FVector camDirection = FVector::Zero();

#pragma region MouseInput
	FVector2D mousePos = FVector2D::Zero();
	if (MouseCanMove && PC->GetMousePosition(mousePos.X, mousePos.Y))
	{
		FVector2D ScreenSize;
		GEngine->GameViewport->GetViewportSize(ScreenSize);
		//margin is window size related
		FVector2D margin = FVector2D(ScreenSize.X * MarginRatio, ScreenSize.Y * MarginRatio);

		//Percent of border proximity, for some reason upper left is 0;0 and bottom right is pixel maximum;maximum of the window
		if (mousePos.X <= margin.X) //Left
		{
			camDirection.Y = ((margin.X - mousePos.X) / margin.X) * -1;
		}
		else if (mousePos.X >= ScreenSize.X - margin.X) //Right
		{
			camDirection.Y = ((mousePos.X - (ScreenSize.X - margin.X)) / margin.X);
		}

		if (mousePos.Y <= margin.Y) //Up
		{
			camDirection.X = (margin.Y - mousePos.Y) / margin.Y;
		}
		else if (mousePos.Y >= ScreenSize.Y - margin.Y) //Down
		{
			camDirection.X = ((mousePos.Y - (ScreenSize.Y - margin.Y)) / margin.Y) * -1;
		}
		camDirection = camDirection.GetClampedToMaxSize(1.0f);
	}
#pragma endregion MouseInput

	if (InputCanMove)
	{
		camDirection += FVector(MovementVector.X, MovementVector.Y,0);
	}

	//Local to World space
	FVector forward = RootScene->GetForwardVector() * camDirection.X;
	FVector right = RootScene->GetRightVector() * camDirection.Y;
	camDirection = forward + right;
	camDirection.Z = 0; //To avoid height movement

	return camDirection;
}

void ACameraPawn::HeightCheck(float DeltaTime)
{
	FHitResult hit;
	FVector start = CameraComp->GetComponentLocation();
	FVector end = start - FVector(0,0,10000);
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByObjectType(hit, start, end, HeightCheckTypes, collisionParams);
		FColor lineColor = hit.bBlockingHit ? FColor::Green : FColor::Red;
	if (hit.bBlockingHit)
	{
		FVector ActorLocation = GetActorLocation();
		ActorLocation.Z = FMath::Lerp(ActorLocation.Z, hit.ImpactPoint.Z + HeightOffset, HeightLerpSpeed * DeltaTime);
		SetActorLocation(ActorLocation, false);
	}
}

//Need to be a latent action
void ACameraPawn::CenterMouse()
{
	if (!PC) { PC = Cast<APlayerController>(GetController()); }	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
			FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(PC);
			FVector2D CenterPosition = ViewportSize * 0.5f;
			int32 X = FMath::TruncToInt(CenterPosition.X);
			int32 Y = FMath::TruncToInt(CenterPosition.Y);
			PC->SetMouseLocation(X, Y);
	}, 0.01f, false);
}
