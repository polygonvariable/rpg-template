#include "Classes/Entity/ECharacter.h"

AECharacter::AECharacter()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	if (SpringArm) {
		SpringArm->SetupAttachment(GetRootComponent());
		SpringArm->TargetArmLength = 400.f;
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera) {
		Camera->SetupAttachment(SpringArm);
	}

}

void AECharacter::CameraPan(float pitch, float yaw)
{
	
	AddControllerYawInput(yaw);
	AddControllerPitchInput(pitch);

}

void AECharacter::CameraZoom(float delta)
{
	
	float currentLength = SpringArm->TargetArmLength;
	SpringArm->TargetArmLength = FMath::Clamp(currentLength + delta, CameraZoomMin, CameraZoomMax);

}

void AECharacter::SimpleMove_Implementation(FVector direction)
{

	float x = direction.X;
	float y = direction.Y;

	FRotator rotation = GetControlRotation();
	float rotX = rotation.Roll;
	float rotZ = rotation.Yaw;

	FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(rotX, 0.0f, rotZ));
	FVector forwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, 0.0f, rotZ));

	AddMovementInput(rightVector, x, false);
	AddMovementInput(forwardVector, y, false);

}
