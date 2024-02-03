// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/DataTable.h"
#include "DebugSystem/GC_DebugSystem.h"
#include "GC_PooledObjectInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGC_PooledObjectInterface : public UInterface
{
	GENERATED_BODY()
};


class GENERICCLASSES_API IGC_PooledObjectInterface
{
	friend class UGC_ObjectPooler;

	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	virtual void OnPooledObjectCreated(FDataTableRowHandle creationDataHandle) {};
	virtual void OnPooledObjectDestroyed() {};

	UFUNCTION(BlueprintNativeEvent)
		void BeginPlay_PooledObject();
	UFUNCTION(BlueprintNativeEvent)
		void BeginDestroy_PooledObject();

	template<typename T>
	T* GetRow(FDataTableRowHandle rowHandle);
};

template<typename T>
T* IGC_PooledObjectInterface::GetRow(FDataTableRowHandle rowHandle)
{
	FString ContextString = TEXT("GetRow from PooledObjectInterface context");

	GC_CHECK_AND_DO(rowHandle.DataTable == nullptr, TEXT("Recieved a nullptr datatable"), {
		return nullptr;
		});

	T* handleRow = rowHandle.DataTable->FindRow<T>(rowHandle.RowName, ContextString, true);

	GC_CHECK(handleRow == nullptr, TEXT("TableRowBase class recieved doesn't match the type of the row passed in the handle"));

	return handleRow;
}
