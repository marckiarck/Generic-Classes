// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/GameData/GC_GameData.h"
#include "SingletonRegister/GC_SingletonRegister.h"
#include "ObjectPooler/GC_ObjectPooler.h"
#include "DataStructures/GC_Wrapper.h"

void UGC_GameData::OnResetInstance_Implementation(FDataTableRowHandle singletonDataHandle)
{
	dataMap.Empty();
}

void UGC_GameData::SaveIntData(const FString& category, const FString& dataIdentifier, int intData)
{
	UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();

	UGC_integerWrapper* Integer = objectPooler->NewUObject<UGC_integerWrapper>();
	Integer->Set(intData);

	SaveData<UGC_integerWrapper>(category, dataIdentifier, Integer);
}

int UGC_GameData::GetIntData(const FString& category, const FString& dataIdentifier)
{
	UGC_integerWrapper* Integer = GetData<UGC_integerWrapper>(category, dataIdentifier);

	if (Integer)
	{
		return Integer->Get();
	}
	
	return 0;
}
