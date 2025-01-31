#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lifecycle/LifeCycleUtils.h"
#include "EActor.generated.h"


UCLASS(DisplayName = "Extended Actor")
class RPGTEMPLATE_API AEActor : public AActor, public ILifeCycleInterface
{

	GENERATED_BODY()
	
public:

	AEActor();

	UPROPERTY(Interp, EditAnywhere, BlueprintReadOnly, Category = "Extended Actor", Meta = (ExposeOnSpawn = true))
	bool bAutoBegin = false;


};
