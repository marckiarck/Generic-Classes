// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SingletonRegister/GC_Singleton.h"
#include "DebugSystem/GC_DebugSystem.h"
#include "GC_GameData.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct GENERICCLASSES_API FGC_DataCategory
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient)
	TMap<FString, UObject*> categoryMap;

};

UCLASS()
class GENERICCLASSES_API UGC_GameData : public UObject, public IGC_Singleton
{
	GENERATED_BODY()
	
	UPROPERTY(Transient)
	TMap<FString, FGC_DataCategory> dataMap;

public:
	template<typename T>
	void SaveData(const FString& category, const FString& dataIdentifier, T* dataObject);
	void SaveIntData(const FString& category, const FString& dataIdentifier, int intData);

	template<typename T>
	T* GetData(const FString& category, const FString& dataIdentifier);
	int GetIntData(const FString& category, const FString& dataIdentifier);

	void OnResetInstance_Implementation(FDataTableRowHandle singletonDataHandle) override;

};

template<typename T>
void UGC_GameData::SaveData(const FString& category, const FString& dataIdentifier, T* data)
{
	if (dataMap.Contains(category) == false)
	{
		dataMap.Add(category, FGC_DataCategory());
	}

	FGC_DataCategory& dataCategory = dataMap[category];
	TMap<FString, UObject*>& categoryMap = dataCategory.categoryMap;

	if (categoryMap.Contains(dataIdentifier))
	{
		categoryMap[dataIdentifier] = data;
	}
	else
	{
		categoryMap.Add(dataIdentifier, data);
	}
}

template<typename T>
T* UGC_GameData::GetData(const FString& category, const FString& dataIdentifier)
{
	T* returnedData = nullptr;

	if (dataMap.Contains(category))
	{
		FGC_DataCategory& dataCategory = dataMap[category];
		TMap<FString, UObject*>& categoryMap = dataCategory.categoryMap;

		if (categoryMap.Contains(dataIdentifier))
		{
			returnedData = Cast<T>(categoryMap[dataIdentifier]);

			GC_CHECK(returnedData == nullptr, FString::Printf(TEXT("%s Data identifier of %s category doesn't match with the specified object class"), *dataIdentifier, *category));
		}
		else
		{
			GC_CHECK(false, FString::Printf(TEXT("%s Data identifier of %s category doesn't exist"), *dataIdentifier, *category));
		}
	}
	else
	{
		GC_CHECK(false, FString::Printf(TEXT("%s Data category doesn't exist"), *category));
	}

	return returnedData;
}
