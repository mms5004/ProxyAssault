// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputInterface.h"
#include "HUDInterface.h"
#include "CameraPawn.generated.h"

UCLASS()
class PROXYASSAULT_API ACameraPawn : public APawn, public IControllerInputInterface
{
	GENERATED_BODY()

public:
	// Sets default values
	ACameraPawn();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	bool MouseCanMove = true;
	UPROPERTY(BlueprintReadWrite)
	bool InputCanMove = true;

	TScriptInterface<IHUDInterface> HUDInterfaceInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MarginRatio = 0.125f;

	//Camera Movement
	UPROPERTY(BlueprintReadWrite)
	float ScrollMultiplicator = 10;
	UPROPERTY(BlueprintReadWrite)
	float ZoomMultiplicator = 100;
	UPROPERTY(BlueprintReadWrite)

	//Height
	FVector2D CameraHeightLimit = FVector2D(300, 3000);
	UPROPERTY(BlueprintReadWrite)
	UCurveFloat* Curve;
	UPROPERTY(BlueprintReadWrite)
	float HeightOffset = 500;
	UPROPERTY(BlueprintReadWrite, Category = "Camera", meta=(MultiLine="true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> HeightCheckTypes;
	UPROPERTY(BlueprintReadWrite)
	float HeightLerpSpeed = 2.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MovementSpeed;

	//Interface functions override
	void Movement_Implementation(FVector2D Direction) override;
	void Zoom_Implementation(float Enhanced) override;
	void Control_Implementation(bool Enabled) override;
	void Shift_Implementation(bool Enabled) override;
	void InputEnable_Implementation() override;
	void LeftClick_Implementation(bool Enabled) override;
	void PlayUnit_Implementation() override;
private:
	UFUNCTION()
	FVector CameraPan();

	UFUNCTION()
	void HeightCheck(float DeltaTime);

	UFUNCTION()
	void CenterMouse();

	UPROPERTY()
	APlayerController* PC;

	UPROPERTY()
	FVector2D MovementVector;

	bool IsShifting;
	bool IsCtrl;
	FTimerHandle TimerHandle;
	
};