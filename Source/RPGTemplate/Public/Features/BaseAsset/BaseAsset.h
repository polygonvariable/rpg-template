#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseAsset.generated.h"


UCLASS(DisplayName = "Base Asset")
class RPGTEMPLATE_API UBaseAsset : public UPrimaryDataAsset
{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Asset")
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Asset")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Asset")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Asset")
	FSoftObjectPath Icon;

};
