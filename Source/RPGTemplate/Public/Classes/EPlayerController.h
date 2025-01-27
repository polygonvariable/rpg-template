#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EPlayerController.generated.h"


UCLASS(DisplayName = "Extended Player Controller")
class RPGTEMPLATE_API AEPlayerController : public APlayerController
{


	GENERATED_BODY()
	

public:



protected:


	UFUNCTION(BlueprintCallable, Category = "Extended Player Controller|Input", Meta = (BlueprintProtected, BlueprintPure))
	UEnhancedInputLocalPlayerSubsystem* GetInputSubsystem();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Extended Player Controller|Input", Meta = (ForceAsFunction, BlueprintProtected))
	void RegisterInput(UInputMappingContext* Context);
	virtual void RegisterInput_Implementation(UInputMappingContext* Context);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Extended Player Controller|Input", Meta = (ForceAsFunction, BlueprintProtected))
	void UnregisterInput(UInputMappingContext* Context);
	virtual void UnregisterInput_Implementation(UInputMappingContext* Context);


};
