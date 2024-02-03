// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GC_Singleton.h"
#include "GC_SingletonRegister.generated.h"


UCLASS(BlueprintType, Blueprintable)
class GENERICCLASSES_API UGC_SingletonRegister : public UObject
{
    GENERATED_BODY()

private:
    UPROPERTY(Transient)
    TMap<FName, UObject*> registeredSingletonsMap;

public:
    static UGC_SingletonRegister* GetSingletonRegister();

    template<typename T>
    static T* GetInstance(FDataTableRowHandle singletonDataHandle = FDataTableRowHandle());

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = Singleton, meta = (DeterminesOutputType = "objectClass", DynamicOutputParam = "outObject"))
    static void GetInstance(TSubclassOf<UObject> objectClass, UObject*& outObject, FDataTableRowHandle singletonDataHandle = FDataTableRowHandle());

    TMap<FName, UObject*> GetRegisteredSingletonMap();

private:
    template<typename T>
    static FName GetSingletonKey();

    static void SendRecoverInstanceLog(FName lostInstanceKey);

};

template<typename T>
T* UGC_SingletonRegister::GetInstance(FDataTableRowHandle singletonDataHandle)
{
    UGC_SingletonRegister* instance = GetSingletonRegister();
    if (instance == nullptr)
    {
        return nullptr;
    }

    T* objectInstance = nullptr;
    const FName singletonKey = GetSingletonKey<T>();
    if (instance->registeredSingletonsMap.Contains(singletonKey))
    {
        objectInstance = Cast<T>(instance->registeredSingletonsMap[singletonKey]);
        if (objectInstance && objectInstance->IsValidLowLevel())
        {
            if (IGC_Singleton* singletonInterface = Cast<IGC_Singleton>(objectInstance))
            {
                singletonInterface->Execute_OnGetInstance(objectInstance, singletonDataHandle);
            }

            return objectInstance;
        }
        else
        {
            SendRecoverInstanceLog(GetSingletonKey<T>());
        }

    }

    objectInstance = NewObject<T>();
    instance->registeredSingletonsMap.Add(singletonKey, objectInstance);

    if (IGC_Singleton* singletonInterface = Cast<IGC_Singleton>(objectInstance))
    {
        singletonInterface->Execute_OnInstanceCreated(objectInstance, singletonDataHandle);
    }

    ensureMsgf(objectInstance, TEXT("Something went wrong during getting singleton instance"));
    return objectInstance;
}

template<typename T>
FName UGC_SingletonRegister::GetSingletonKey()
{
    return FName(T::StaticClass()->GetName());
}
