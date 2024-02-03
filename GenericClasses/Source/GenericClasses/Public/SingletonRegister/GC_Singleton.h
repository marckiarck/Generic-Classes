// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/DataTable.h"
#include "GC_Singleton.generated.h"



// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGC_Singleton : public UInterface
{
	GENERATED_BODY()
};


class GENERICCLASSES_API IGC_Singleton
{

	friend class UGC_SingletonRegister;

	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Singleton)
		void OnResetInstance(FDataTableRowHandle singletonDataHandle);

protected:
	UFUNCTION(BlueprintNativeEvent)
		void OnInstanceCreated(FDataTableRowHandle singletonDataHandle);

	UFUNCTION(BlueprintNativeEvent)
		void OnGetInstance(FDataTableRowHandle singletonDataHandle);
};
