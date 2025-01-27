#include "Classes/EPlayerController.h"

UEnhancedInputLocalPlayerSubsystem* AEPlayerController::GetInputSubsystem()
{

	if (!IsLocalPlayerController()) {
		return nullptr;
	}

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer)
	{
		return nullptr;
	}

	if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		return InputSystem;
	}

	return nullptr;

}

void AEPlayerController::RegisterInput_Implementation(UInputMappingContext* Context)
{

	if (UEnhancedInputLocalPlayerSubsystem* InputSystem = GetInputSubsystem())
	{
		InputSystem->AddMappingContext(Context, 0);
	}

}

void AEPlayerController::UnregisterInput_Implementation(UInputMappingContext* Context)
{

	if (UEnhancedInputLocalPlayerSubsystem* InputSystem = GetInputSubsystem())
	{
		InputSystem->RemoveMappingContext(Context);
	}

}
