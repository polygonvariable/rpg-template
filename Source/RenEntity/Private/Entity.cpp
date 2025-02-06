// Fill out your copyright notice in the Description page of Project Settings.

// Parent Header
#include "Entity.h"

// Engine Headers
#include "Components/CapsuleComponent.h"


AEntity::AEntity()
{
	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCapsuleHalfHeight(90.0f);
		Capsule->SetCapsuleRadius(35.0f);
	}
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();
}

void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}