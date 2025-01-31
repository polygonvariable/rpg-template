// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnhanceLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UEnhanceLibrary : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

public:

	static int CalculateLevelUpProgression(int Level, int Value, int ValueProgression);
	
	static bool CalculateEnhance(
		int EnhancePoint,
		int CurrentXp,
		int CurrentLevel,
		int CurrentRank,
		int XpInterval,
		int LevelInterval,
		int MaxLevel,

		int& NewXp,
		int& NewLevel,
		bool& bDoesLevelUpdated,
		bool& bDoesRankShouldUpdate,
		bool& bDoesMaxLevelReached
	);

	static bool CanRankUp(int CurrentXp, int CurrentLevel, int LevelInterval);
	
};
