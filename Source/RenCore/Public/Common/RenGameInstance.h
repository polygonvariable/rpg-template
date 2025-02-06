// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// Generated Headers
#include "RenGameInstance.generated.h"


/**
 * 
 */
UCLASS(DisplayName = "Ren Game Instance")
class RENCORE_API URenGameInstance : public UGameInstance
{

	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialized();

public:

	virtual void Init() override;

};