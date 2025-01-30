#pragma once

#include "CoreMinimal.h"

#include "BaseUtil.generated.h"


USTRUCT(BlueprintType, DisplayName = "Base Asset Filter Rule")
struct FBaseAssetFilterRule
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableIdFilter = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableStrictId = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> IncludedIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> ExcludedIds;

	bool MatchId(FName Id) const
	{
		if (!bEnableIdFilter) return true;
		if (ExcludedIds.Contains(Id)) return false;
		if (bEnableStrictId && IncludedIds.Num() == 0) return false;
		if (IncludedIds.Num() > 0) return IncludedIds.Contains(Id);
		return true;
	}

	bool Matches(FName Id) const
	{
		return MatchId(Id);
	}

};