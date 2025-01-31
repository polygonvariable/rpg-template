#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeCycle/LifeCycleUtils.h"
#include "EActorComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), DisplayName = "Extended Actor Component")
class RPGTEMPLATE_API UEActorComponent : public UActorComponent, public ILifeCycleInterface
{

	GENERATED_BODY()

public:

	UEActorComponent();

};
