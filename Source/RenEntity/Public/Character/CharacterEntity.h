// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Project Headers
#include "Entity.h"

// Generated Headers
#include "CharacterEntity.generated.h"

// Forward Declarations
class USpringArmComponent;
class UCameraComponent;


/**
 *
 */
//UENUM(BlueprintType, DisplayName = "Sub Movement Type")
//enum ESubMovement
//{
//	Idle UMETA(DisplayName = "Idle"),
//	Walk UMETA(DisplayName = "Walk"),
//	Sprint UMETA(DisplayName = "Sprint"),
//	Fall UMETA(DisplayName = "Fall")
//};




/**
 *
 */
UCLASS(Abstract, DisplayName = "Character Entity")
class RENENTITY_API ACharacterEntity : public AEntity
{

	GENERATED_BODY()

public:

	ACharacterEntity();


	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	//TEnumAsByte<ESubMovement> CurrentSubMovement = ESubMovement::Idle;
	//UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Default")
	//bool bCanSprint = false;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<USpringArmComponent> SpringArm;


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<UCameraComponent> Camera;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Entity|Input")
	float CameraMinZoom = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Entity|Input")
	float CameraMaxZoom = 2000.0f;

	UFUNCTION(BlueprintCallable, Category = "Character Entity|Input", Meta = (BlueprintProtected))
	void CameraPan(const FVector2D Axis);

	UFUNCTION(BlueprintCallable, Category = "Character Entity|Input", Meta = (BlueprintProtected))
	void CameraZoom(const float Delta, const float Multiplier = 5.0f);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character Entity|Input", Meta = (ForceAsFunction, BlueprintProtected))
	void SimpleMove(FVector Direction);
	virtual void SimpleMove_Implementation(FVector Direction);


	//virtual void Tick(float DeltaTime) override;

};

