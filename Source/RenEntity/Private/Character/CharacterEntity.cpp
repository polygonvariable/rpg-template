// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Character/CharacterEntity.h"

// Engine Headers
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

// Project Headers
#include "RenGlobal/Public/Macro/LogMacro.h"
#include "WeaponTest.h"


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

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

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

void ACharacterEntity::CameraPan(const FVector2D Axis)
{
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void ACharacterEntity::CameraZoom(const float Delta, const float Multiplier)
{
	if(!IsValid(SpringArm))
	{
		return;
	}

	float CurrentLength = SpringArm->TargetArmLength;
	SpringArm->TargetArmLength = FMath::Clamp(CurrentLength + (Delta * Multiplier), CameraMinZoom, CameraMaxZoom);
}


void ACharacterEntity::SimpleMove_Implementation(FVector direction)
{
	FRotator Rotation = GetControlRotation();
	FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0.0f, Rotation.Yaw, Rotation.Roll));
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, Rotation.Yaw, 0.0f));

	AddMovementInput(RightVector, direction.X, false);
	AddMovementInput(ForwardVector, direction.Y, false);
}

void ACharacterEntity::DealDamage(TSubclassOf<UGameplayEffect> EffectClass, AActor* Target, AActor* EffectCauser)
{
	UAbilitySystemComponent* TargetASC = Target->GetComponentByClass<UAbilitySystemComponent>();

	if (IsValid(AbilitySystemComponent) && IsValid(TargetASC))
	{
		TArray<TWeakObjectPtr<AActor>> ContextActors;
		for (AActor* Actor : OwnedActors)
		{
			ContextActors.Add(TWeakObjectPtr<AActor>(Actor));
		}

		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		EffectContext.AddActors(ContextActors);
		EffectContext.AddOrigin(GetActorLocation());
		EffectContext.AddInstigator(this, EffectCauser);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, EffectContext);

		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
	}
}

void ACharacterEntity::SpawnWeapon()
{
	if (IsValid(Weapon) || !GetWorld())
	{
		PRINT_ERROR(LogTemp, 1.0f, TEXT("Weapon is already spawned or World is not valid"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;

	Weapon = GetWorld()->SpawnActor<AWeaponTest>(WeaponClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	if (IsValid(Weapon))
	{
		OwnedActors.Add(Weapon);
	}

	PRINT_WARNING(LogTemp, 1.0f, TEXT("Weapon spawned"));
}


//void ACharacterEntity::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
//	{
//		EMovementMode Mode = MovementComponent->MovementMode;
//		switch (Mode)
//		{
//			case EMovementMode::MOVE_Walking:
//				if (GetVelocity().IsNearlyZero(50.0f))
//				{
//					CurrentSubMovement = ESubMovement::Idle;
//				}
//				else if (GetVelocity().Size2D() > 50.0f && GetVelocity().Size2D() < 500.0f || !bCanSprint)
//				{
//					CurrentSubMovement = ESubMovement::Walk;
//				}
//				else if (GetVelocity().Size2D() > 500.0f && bCanSprint)
//				{
//					CurrentSubMovement = ESubMovement::Sprint;
//				}
//				break;
//			case EMovementMode::MOVE_Falling:
//				CurrentSubMovement = ESubMovement::Fall;
//				break;
//		}
//	}
//}
// On_Jump_Pressed -> Give jump ability
// On_Jump_Released -> Remove jump ability

