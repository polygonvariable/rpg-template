// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstancedStruct.h"

// Generated Headers
#include "RegionActor.generated.h"


/**
 *
 */
UCLASS()
class RENENVIRONMENT_API ARegionActor : public AActor
{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	FInstancedStruct RegionConfiguration;

protected:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Handler")
	void OnPlayerEntered();
	virtual void OnPlayerEntered_Implementation();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction, BlueprintProtected), Category = "Handler")
	void OnPlayerExited();
	virtual void OnPlayerExited_Implementation();

};
