// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GC_ObjectPool.h"
#include "GC_PooledObjectInterface.h"
#include "GC_ObjectPooler.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDestroyed, UObject*);

UCLASS()
class GENERICCLASSES_API UGC_ObjectPooler : public UObject
{
    GENERATED_BODY()

private:
    UPROPERTY(Transient)
    TMap<FName, UGC_ObjectPool*> poolsMap;

    FOnPooledObjectDestroyed onPooledObjectDestroyedDelegate;

public:
    template<typename T>
    T* NewUObject(FDataTableRowHandle creationDataHandle = FDataTableRowHandle());

    template<typename T>
    T* NewUObject(TSubclassOf<T> objectClass, FDataTableRowHandle creationDataHandle = FDataTableRowHandle());

    UFUNCTION(BlueprintCallable, Category = ObjectPooler, meta = (DeterminesOutputType = "objectClass", DynamicOutputParam = "spawnedActor"))
    void CreateObject(TSubclassOf<UObject> objectClass, UObject*& createdObject, FDataTableRowHandle creationDataHandle = FDataTableRowHandle());

    template<typename T>
    T* NewUObjectTemplated(TSubclassOf<T> childClass, FDataTableRowHandle creationDataHandle = FDataTableRowHandle());

    template<typename T>
    void DestroyUObject(T* objectReference);

    UFUNCTION(BlueprintCallable, Category = ObjectPooler)
    void DestroyObject(UObject* objectReference);

    template<typename T>
    T* SpawnActor(ULevel* spawnLevel, UClass* actorClass, FTransform spawnTransForm, FDataTableRowHandle creationDataHandle = FDataTableRowHandle(), bool collisionEnabled = true);

    UFUNCTION(BlueprintCallable, Category = ObjectPooler, meta = (DeterminesOutputType = "actorClass", DynamicOutputParam = "spawnedActor", AdvancedDisplay = "collisionEnabled"))
    void SpawnActor(ULevel* spawnLevel, TSubclassOf<AActor> actorClass, FTransform spawnTransForm, FDataTableRowHandle creationDataHandle, AActor*& spawnedActor, bool collisionEnabled = true);

    UFUNCTION(BlueprintCallable, Category = ObjectPooler)
    void DespawnActor(AActor* actorReference);

    FOnPooledObjectDestroyed& GetOnPooledObjectDestroyed();
    TMap<FName, UGC_ObjectPool*> GetPoolsMap() { return poolsMap; }

private:
    template<typename T>
    FName GetPoolKey();
    FName GetPoolKey(TSubclassOf<UObject> objectClass);

    template<typename T>
    void OnPooledObjectCreated(T* createdObject, FDataTableRowHandle creationDataHandle);

    template<typename T>
    void OnPooledObjectDestroyed(T* destroyedObject);
};

template<typename T>
T* UGC_ObjectPooler::NewUObject(FDataTableRowHandle creationDataHandle)
{
    return NewUObject<T>(T::StaticClass(), creationDataHandle);
}

template<typename T>
T* UGC_ObjectPooler::NewUObject(TSubclassOf<T> objectClass, FDataTableRowHandle creationDataHandle)
{
    if (objectClass == nullptr)
    {
        ensureMsgf(false, TEXT("Trying to instance a nullptr class"));
        return nullptr;
    }

    if (objectClass->HasAnyClassFlags(CLASS_Abstract))
    {
        ensureMsgf(false, TEXT("Trying to instance an abstract class"));
        return nullptr;
    }

    T* pooledObject = nullptr;

    FName poolKey = GetPoolKey(objectClass);
    if (poolsMap.Contains(poolKey))
    {
        UGC_ObjectPool* pool = poolsMap[poolKey];
        pooledObject = pool->GetObjectFromPool<T>();

        if (pooledObject == nullptr)
        {
            pooledObject = NewObject<T>(this, objectClass);
            pool->AddObjectToPool(pooledObject);
        }

    }
    else
    {
        UGC_ObjectPool* newPool = NewObject<UGC_ObjectPool>();
        pooledObject = NewObject<T>(this, objectClass);
        poolsMap.Add(poolKey, newPool);
        newPool->AddObjectToPool(pooledObject);
    }

    OnPooledObjectCreated<T>(pooledObject, creationDataHandle);

    ensureMsgf(pooledObject, TEXT("Something went wrong during object creation"));
    return pooledObject;
}

template<typename T>
T* UGC_ObjectPooler::NewUObjectTemplated(TSubclassOf<T> childClass, FDataTableRowHandle creationDataHandle)
{
    if (childClass == nullptr)
    {
        ensureMsgf(false, TEXT("Trying to instance a nullptr class"));
        return nullptr;
    }

    if (childClass->HasAnyClassFlags(CLASS_Abstract))
    {
        ensureMsgf(false, TEXT("Trying to instance an abstract class"));
        return nullptr;
    }

    T* pooledObject = nullptr;

    FName poolKey = GetPoolKey(childClass);
    if (poolsMap.Contains(poolKey))
    {
        UGC_ObjectPool* pool = poolsMap[poolKey];
        pooledObject = pool->GetObjectFromPool<T>();

        if (pooledObject == nullptr)
        {
            pooledObject = NewObject<T>(this, childClass);
            pool->AddObjectToPool(pooledObject);
        }

    }
    else
    {
        UGC_ObjectPool* newPool = NewObject<UGC_ObjectPool>();
        pooledObject = NewObject<T>(this, childClass);
        poolsMap.Add(poolKey, newPool);
        newPool->AddObjectToPool(pooledObject);
    }

    OnPooledObjectCreated<T>(pooledObject, creationDataHandle);

    ensureMsgf(pooledObject, TEXT("Something went wrong during object creation"));
    return pooledObject;
}

template<typename T>
void UGC_ObjectPooler::DestroyUObject(T* objectReference)
{
    if (objectReference == nullptr)
    {
        return;
    }

    OnPooledObjectDestroyed<T>(objectReference);

    FName poolKey = GetPoolKey(objectReference->GetClass());
    if (poolsMap.Contains(poolKey))
    {
        UGC_ObjectPool* pool = poolsMap[poolKey];
        pool->RemoveObjectFromPool<T>(objectReference);
    }
    else
    {
        objectReference->ConditionalBeginDestroy();
    }
}

template<typename T>
T* UGC_ObjectPooler::SpawnActor(ULevel* spawnLevel, UClass* actorClass, FTransform spawnTransForm, FDataTableRowHandle creationDataHandle, bool collisionEnabled /*= true*/)
{
    AActor* spawnedActor = nullptr;
    if (actorClass)
    {
        SpawnActor(spawnLevel, actorClass, spawnTransForm, creationDataHandle, spawnedActor, collisionEnabled);
    }
    else
    {
        SpawnActor(spawnLevel, T::StaticClass(), spawnTransForm, creationDataHandle, spawnedActor, collisionEnabled);
    }

    ensureMsgf(spawnedActor, TEXT("Something went wrong during object creation"));
    return Cast<T>(spawnedActor);
}

template<typename T>
FName UGC_ObjectPooler::GetPoolKey()
{
    return FName(T::StaticClass()->GetName());
}

template<typename T>
void UGC_ObjectPooler::OnPooledObjectCreated(T* createdObject, FDataTableRowHandle creationDataHandle)
{

    if (IGC_PooledObjectInterface* pooledObjectInterface = Cast<IGC_PooledObjectInterface>(createdObject))
    {
        pooledObjectInterface->OnPooledObjectCreated(creationDataHandle);
        pooledObjectInterface->Execute_BeginPlay_PooledObject(createdObject);
    }
}

template<typename T>
void UGC_ObjectPooler::OnPooledObjectDestroyed(T* destroyedObject)
{
    onPooledObjectDestroyedDelegate.Broadcast(destroyedObject);

    if (IGC_PooledObjectInterface* pooledObjectInterface = Cast<IGC_PooledObjectInterface>(destroyedObject))
    {
        pooledObjectInterface->OnPooledObjectDestroyed();
        pooledObjectInterface->Execute_BeginDestroy_PooledObject(destroyedObject);
    }
}
