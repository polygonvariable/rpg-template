#pragma once

#include "CoreMinimal.h"
#include "Classes/EEntity.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ECharacter.generated.h"


UCLASS(DisplayName = "Extended Character")
class RPGTEMPLATE_API AECharacter : public AEEntity
{


	GENERATED_BODY()


public:


	AECharacter();


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr< USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<UCameraComponent> Camera;


protected:


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Extended Character|Input")
	float CameraZoomMin = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Extended Character|Input")
	float CameraZoomMax = 2000.0f;

	UFUNCTION(BlueprintCallable, Category = "Extended Character|Input", Meta = (BlueprintProtected))
	void CameraPan(float pitch, float yaw);

	UFUNCTION(BlueprintCallable, Category = "Extended Character|Input", Meta = (BlueprintProtected))
	void CameraZoom(float delta);

	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Extended Character|Input", Meta = (ForceAsFunction, BlueprintProtected))
	void SimpleMove(FVector direction);
	virtual void SimpleMove_Implementation(FVector direction);


};
