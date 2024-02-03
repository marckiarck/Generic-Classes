// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GC_ObjectPool.generated.h"

UCLASS()
class GENERICCLASSES_API UGC_ObjectPool : public UObject
{
    friend class UGC_ObjectPooler;

    GENERATED_BODY()


private:
    UPROPERTY(Transient)
    TArray<UObject*> usedObjects;
    UPROPERTY(Transient)
    TArray<UObject*> freeObjects;

public:
    template<typename T>
    T* GetObjectFromPool();

    template<typename T>
    void RemoveObjectFromPool(T* objectRemoved);

    TArray<UObject*> GetUsedObjects() { return usedObjects; }
    TArray<UObject*> GetFreeObjects() { return freeObjects; }

private:
    void AddObjectToPool(UObject* addedObject);
};

template<typename T>
T* UGC_ObjectPool::GetObjectFromPool()
{
    T* freeObject = nullptr;
    while (freeObjects.Num() > 0)
    {
        freeObject = Cast<T>(freeObjects.Pop());
        if (freeObject && freeObject->IsValidLowLevel())
        {
            usedObjects.Add(freeObject);

            return freeObject;
        }

    }

    return nullptr;
}

template<typename T>
void UGC_ObjectPool::RemoveObjectFromPool(T* objectRemoved)
{
    if (usedObjects.Remove(objectRemoved) > 0)
    {
        if (objectRemoved && objectRemoved->IsValidLowLevel())
        {
            freeObjects.Add(objectRemoved);
        }
    }

}
