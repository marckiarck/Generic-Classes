// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/GameData/GC_GameDataFunctionLibrary.h"
#include "GenericClasses/Public/GenericClassesMinimals.h"

void UGC_GameDataFunctionLibrary::SaveData(const FString& dataCategory, const FString& dataIdentifier, UObject* dataObject)
{
	UGC_GameData* gameData = UGC_SingletonRegister::GetInstance<UGC_GameData>();

	gameData->SaveData<UObject>(dataCategory, dataIdentifier, dataObject);
}

void UGC_GameDataFunctionLibrary::SaveIntData(const FString& dataCategory, const FString& dataIdentifier, int intData)
{
	UGC_GameData* gameData = UGC_SingletonRegister::GetInstance<UGC_GameData>();

	gameData->SaveIntData(dataCategory, dataIdentifier, intData);
}

void UGC_GameDataFunctionLibrary::GetData(const FString& dataCategory, const FString& dataIdentifier, UObject*& dataObject, TSubclassOf<UObject> objetClass)
{
	UGC_GameData* gameData = UGC_SingletonRegister::GetInstance<UGC_GameData>();

	dataObject = gameData->GetData<UObject>(dataCategory, dataIdentifier);
}

int UGC_GameDataFunctionLibrary::GetIntData(const FString& dataCategory, const FString& dataIdentifier)
{
	UGC_GameData* gameData = UGC_SingletonRegister::GetInstance<UGC_GameData>();

	return gameData->GetIntData(dataCategory, dataIdentifier);
}
