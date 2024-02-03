// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/SingletonRegister/GC_SingletonRegister.h"
#include "DebugSystem/GC_DebugSystem.h"
#include "GameInstance/GC_GameInstance.h"
#include "Kismet/GameplayStatics.h"


void UGC_SingletonRegister::GetInstance(TSubclassOf<UObject> objectClass, UObject*& OutActor, FDataTableRowHandle singletonDataHandle)
{
	UGC_SingletonRegister* instance = GetSingletonRegister();
	if (instance == nullptr)
	{
		OutActor = nullptr;
		return ;
	}

	const FName singletonKey = FName(objectClass->GetName());
	if (instance->registeredSingletonsMap.Contains(singletonKey))
	{
		OutActor = instance->registeredSingletonsMap[singletonKey];

		if (OutActor && OutActor->IsValidLowLevel())
		{
			if (IGC_Singleton* singletonInterface = Cast<IGC_Singleton>(OutActor))
			{
				singletonInterface->Execute_OnGetInstance(OutActor, singletonDataHandle);
			}

			ensureMsgf(OutActor, TEXT("Something went wrong during getting singleton instance"));
			return;
		}

	}
	
	OutActor = NewObject<UObject>(instance, objectClass);
	instance->registeredSingletonsMap.Add(singletonKey, OutActor);

	if (IGC_Singleton* singletonInterface = Cast<IGC_Singleton>(OutActor))
	{
		singletonInterface->Execute_OnInstanceCreated(OutActor, singletonDataHandle);
	}

	ensureMsgf(OutActor, TEXT("Something went wrong during getting singleton instance"));
}

TMap<FName, UObject*> UGC_SingletonRegister::GetRegisteredSingletonMap()
{
	return registeredSingletonsMap;
}

void UGC_SingletonRegister::SendRecoverInstanceLog(FName lostInstanceKey)
{
	FString lostInstanceString = lostInstanceKey.ToString();
	UGC_DebugSystem* debugSystem = UGC_SingletonRegister::GetInstance<UGC_DebugSystem>();
	debugSystem->SendLog(FString::Printf(TEXT("Lost reference with %s class"), *lostInstanceString));
}

UGC_SingletonRegister* UGC_SingletonRegister::GetSingletonRegister()
{
	UGC_GameInstance* gameInstance = Cast<UGC_GameInstance>(UGameplayStatics::GetGameInstance(GEngine->GetCurrentPlayWorld()));
	if (gameInstance == nullptr)
	{
		UGC_DebugSystem* debugSystem = NewObject<UGC_DebugSystem>();
		debugSystem->SendLog(TEXT("SingletonRegister is NULL. Game Instance must inherit from UGC_GameInstance to allow Singletons."));

		return nullptr;
	}

	if (gameInstance->singletonInstance == nullptr || gameInstance->singletonInstance->IsValidLowLevel() == false)
	{
		gameInstance->singletonInstance = NewObject<UGC_SingletonRegister>();
		UGC_DebugSystem* debugSystem = gameInstance->singletonInstance->GetInstance<UGC_DebugSystem>();
		debugSystem->SendLog(TEXT("Created Singleton Register instance"));
	}

	return gameInstance->singletonInstance;
}
