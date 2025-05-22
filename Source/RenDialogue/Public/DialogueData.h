// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"

// Generated Headers
#include "DialogueData.generated.h"



/**
 *
 */
USTRUCT(BlueprintType)
struct FDialogueData : public FTableRowBase
{

    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly)
    FText DialogueText;

};

