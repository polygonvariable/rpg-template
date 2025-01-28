#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EGameInstanceSubsystem.generated.h"


UCLASS(Blueprintable, DisplayName = "Extended Game Instance Subsystem")
class RPGTEMPLATE_API UEGameInstanceSubsystem : public UGameInstanceSubsystem
{


	GENERATED_BODY()


public:

	UPROPERTY(Interp, EditAnywhere, Category = "Extended Game Instance Subsystem")
	bool bAllowCreation = false;

	UPROPERTY(Interp, EditAnywhere, Category = "Extended Game Instance Subsystem")
	bool bAllowBlueprint = false;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Extended Game Instance Subsystem")
	void PostInitialize();
	virtual void PostInitialize_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Extended Game Instance Subsystem")
	void OnInitialized();
	virtual void OnInitialized_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Meta = (ForceAsFunction), Category = "Extended Game Instance Subsystem")
	void OnDeinitialized();
	virtual void OnDeinitialized_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Extended Game Instance Subsystem", meta = (DeterminesOutputType = "SubsystemClass"))
	UEGameInstanceSubsystem* GetSubsystem(TSubclassOf<UEGameInstanceSubsystem> SubsystemClass) const;


protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* object) const override;
	virtual UWorld* GetWorld() const override;


};
