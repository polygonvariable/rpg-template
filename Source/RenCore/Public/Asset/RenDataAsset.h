// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "RenDataAsset.generated.h"

/**
 *
 */
UCLASS(DisplayName = "Ren Data Asset")
class RENCORE_API URenDataAsset : public UPrimaryDataAsset
{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset Detail")
	FName AssetId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset Detail")
	FText AssetName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset Detail")
	FText AssetDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset Detail")
	TSoftObjectPtr<UTexture2D> AssetIcon;

};

