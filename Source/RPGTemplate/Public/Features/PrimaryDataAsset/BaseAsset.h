#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseAsset.generated.h"


UCLASS(DisplayName = "BaseAsset")
class RPGTEMPLATE_API UBaseAsset : public UPrimaryDataAsset
{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAsset")
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAsset")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAsset")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseAsset")
	FSoftObjectPath Icon;

};
