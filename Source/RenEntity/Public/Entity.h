// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Generated Headers
#include "Entity.generated.h"


/**
 *
 */
UCLASS(Abstract, DisplayName = "Entity")
class RENENTITY_API AEntity : public ACharacter
{

	GENERATED_BODY()

public:

	AEntity();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};