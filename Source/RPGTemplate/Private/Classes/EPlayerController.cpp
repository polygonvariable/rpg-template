#include "Classes/EPlayerController.h"


UEnhancedInputLocalPlayerSubsystem* AEPlayerController::GetInputSubsystem() const
{
	if (!IsLocalPlayerController())
	{
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

void AEPlayerController::RegisterInput_Implementation(UInputMappingContext* context)
{
	if (UEnhancedInputLocalPlayerSubsystem* InputSystem = GetInputSubsystem())
	{
		InputSystem->AddMappingContext(context, 0);
	}
}

void AEPlayerController::UnregisterInput_Implementation(UInputMappingContext* context)
{
	if (UEnhancedInputLocalPlayerSubsystem* InputSystem = GetInputSubsystem())
	{
		InputSystem->RemoveMappingContext(context);
	}
}
