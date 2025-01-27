#include "Classes/Entity/ECharacter.h"

AECharacter::AECharacter() : Super()
{


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	if (SpringArm) {
		SpringArm->SetupAttachment(GetRootComponent());
		SpringArm->TargetArmLength = 400.f;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritRoll = false;
		SpringArm->bEnableCameraLag = true;
		SpringArm->bEnableCameraRotationLag = true;
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera) {
		Camera->SetupAttachment(SpringArm);
	}

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{

		MovementComponent->GravityScale = 1.75f;
		MovementComponent->MaxAcceleration = 1500.0f;
		MovementComponent->bUseSeparateBrakingFriction = true;

		MovementComponent->MaxWalkSpeed = 500.0f;
		MovementComponent->MinAnalogWalkSpeed = 20.0f;
		MovementComponent->BrakingDecelerationWalking = 2000.0f;

		MovementComponent->BrakingDecelerationFalling = 1500.0f;
		MovementComponent->AirControl = 0.35f;

		MovementComponent->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
		MovementComponent->bOrientRotationToMovement = true;
		
	}

	bUseControllerRotationYaw = false;

}

void AECharacter::CameraPan(FVector2D axis)
{
	
	AddControllerYawInput(axis.X);
	AddControllerPitchInput(axis.Y);

}

void AECharacter::CameraZoom(float delta)
{
	
	float currentLength = SpringArm->TargetArmLength;
	SpringArm->TargetArmLength = FMath::Clamp(currentLength + delta, cameraZoomMin, cameraZoomMax);

}

void AECharacter::SimpleMove_Implementation(FVector direction)
{

	float x = direction.X;
	float y = direction.Y;

	FRotator rotation = GetControlRotation();
	float rotX = rotation.Roll;
	float rotZ = rotation.Yaw;

	FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(0.0f, rotZ, rotX));
	FVector forwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, rotZ, 0.0f));

	AddMovementInput(rightVector, x, false);
	AddMovementInput(forwardVector, y, false);

}
