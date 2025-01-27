#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EActor.generated.h"


UCLASS(DisplayName = "Extended Actor")
class RPGTEMPLATE_API AEActor : public AActor
{

	GENERATED_BODY()
	
public:

	AEActor();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

};
