// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterUtils.generated.h"


USTRUCT(BlueprintType, DisplayName = "Filter Name Rule")
struct FFilterNameRule
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (InlineEditConditionToggle))
	bool bEnable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bEnable"))
	bool bEnableStrictMode = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bEnable"))
	TArray<FName> Included;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bEnable"))
	TArray<FName> Excluded;

	bool Matches(FName Value) const
	{
		if (!bEnable) return true;
		if (Excluded.Contains(Value)) return false;
		if (bEnableStrictMode && Included.Num() == 0) return false;
		if (Included.Num() > 0) return Included.Contains(Value);
		return true;
	}

};

USTRUCT(BlueprintType, DisplayName = "Filter Integer Rule")
struct FFilterIntegerRule
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (InlineEditConditionToggle))
	bool bEnable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bEnable"))
	bool bEnableStrictMode = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bEnable"))
	int32 Min = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bEnable"))
	int32 Max = 0;

	bool Matches(int32 Value) const
	{
		if (!bEnable) return true;
		if (bEnableStrictMode)
		{
			return Value > Min && Value < Max;
		}
		else
		{
			return Value >= Min && Value <= Max;
		}
	}

};

UENUM(BlueprintType, DisplayName = "Filter Combination")
enum class EFilterCombination : uint8
{
	And UMETA(DisplayName = "AND"),
	Or UMETA(DisplayName = "OR")
};