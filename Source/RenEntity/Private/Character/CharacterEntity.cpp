// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Character/CharacterEntity.h"

// Engine Headers
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


ACharacterEntity::ACharacterEntity() : Super()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (IsValid(SpringArm))
	{
		SpringArm->SetupAttachment(GetRootComponent());
		SpringArm->TargetArmLength = 400.f;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritRoll = false;
		SpringArm->bEnableCameraLag = true;
		SpringArm->bEnableCameraRotationLag = true;
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (IsValid(Camera))
	{
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

void ACharacterEntity::CameraPan(FVector2D Axis)
{
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void ACharacterEntity::CameraZoom(float Delta, float Multiplier)
{
	float CurrentLength = SpringArm->TargetArmLength;
	SpringArm->TargetArmLength = FMath::Clamp(CurrentLength + (Delta * Multiplier), CameraMinZoom, CameraMaxZoom);
}

void ACharacterEntity::SimpleMove_Implementation(FVector direction)
{
	float X = direction.X;
	float Y = direction.Y;

	FRotator Rotation = GetControlRotation();
	float RotationX = Rotation.Roll;
	float RotationZ = Rotation.Yaw;

	FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0.0f, RotationZ, RotationX));
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, RotationZ, 0.0f));

	AddMovementInput(RightVector, X, false);
	AddMovementInput(ForwardVector, Y, false);
}