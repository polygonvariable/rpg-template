#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "InstancedStruct.h"
#include "ESaveGame.generated.h"


UCLASS(DisplayName = "Extended SaveGame")
class RPGTEMPLATE_API UESaveGame : public USaveGame
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TMap<FName, FInstancedStruct> NamedSlots;

	UFUNCTION(BlueprintCallable, Category = "Extended SaveGame|Slots")
	bool AddSlot(FName Name, FInstancedStruct Slot);

	UFUNCTION(BlueprintCallable, Category = "Extended SaveGame|Slots")
	bool RemoveSlot(FName Name, FInstancedStruct Slot);

	UFUNCTION(BlueprintCallable, Category = "Extended SaveGame|Slots")
	bool UpdateSlot(FName Name, FInstancedStruct Slot);

	UFUNCTION(BlueprintCallable, Category = "Extended SaveGame|Slots")
	FInstancedStruct GetSlot(FName Name, bool & bSuccess);


	UPROPERTY(EditAnywhere, Category = "Extended SaveGame|Environment")
	TMap<FGuid, FDateTime> StampChanges;

};
