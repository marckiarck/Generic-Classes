// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GC_GameDataFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UGC_GameDataFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "GameData")
		static void SaveData(const FString& dataCategory, const FString& dataIdentifier, UObject* dataObject);
	UFUNCTION(BlueprintCallable, Category = "GameData")
		static void SaveIntData(const FString& dataCategory, const FString& dataIdentifier, int intData);

	UFUNCTION(BlueprintCallable, Category = "GameData", meta = (DeterminesOutputType = "objetClass", DynamicOutputParam = "dataObject"))
		static void GetData(const FString& dataCategory, const FString& dataIdentifier, UObject*& dataObject, TSubclassOf<UObject> objetClass);
	UFUNCTION(BlueprintCallable, Category = "GameData")
		static int GetIntData(const FString& dataCategory, const FString& dataIdentifier);
};
