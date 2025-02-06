// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "RenBaseAsset.generated.h"

/**
 *
 */
UCLASS(DisplayName = "Ren Base Asset")
class RENCORE_API URenBaseAsset : public UPrimaryDataAsset
{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Details")
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Details")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Details")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Details")
	TSoftObjectPtr<UTexture2D> Icon;

};

