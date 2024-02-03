

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GC_DebugObject.h"
#include <Engine/DataAsset.h>
#include "SingletonRegister/GC_Singleton.h"
#include "GC_DebugObjectManager.generated.h"

UCLASS()
class GENERICCLASSESDEBUG_API UGC_DebugObjectDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGC_DebugObject>> enabledDebugObjects;
};

UCLASS()
class GENERICCLASSESDEBUG_API UGC_DebugObjectManager : public UObject, public IGC_Singleton
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Transient)
	TMap<FString, UGC_DebugObject*> registeredDebugObjects;

	UPROPERTY(Transient)
	UGC_DebugObject* mainDebugObject = nullptr;

public:
	void InitializeDebugObjects();
	void AddDebugObject(TSubclassOf<UGC_DebugObject> debugObjectClass);

	UFUNCTION(Exec)
	void EnableDebugObject(FString debugObject);
	
	UGC_DebugObject* GetMainDebugObject();

protected:
	void OnInstanceCreated_Implementation(FDataTableRowHandle singletonDataHandle) override;

private:
	void CreateDebugObjectsDataTable();


};
