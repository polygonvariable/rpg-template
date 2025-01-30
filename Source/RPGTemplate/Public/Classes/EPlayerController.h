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
	
protected:

	UFUNCTION(BlueprintCallable, Category = "Extended Player Controller|Input", Meta = (BlueprintProtected, BlueprintPure))
	UEnhancedInputLocalPlayerSubsystem* GetInputSubsystem() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Extended Player Controller|Input", Meta = (ForceAsFunction, BlueprintProtected))
	void RegisterInput(UInputMappingContext* MappingContext);
	virtual void RegisterInput_Implementation(UInputMappingContext* MappingContext);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Extended Player Controller|Input", Meta = (ForceAsFunction, BlueprintProtected))
	void UnregisterInput(UInputMappingContext* MappingContext);
	virtual void UnregisterInput_Implementation(UInputMappingContext* MappingContext);

};
