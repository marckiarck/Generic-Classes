// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/ObjectPooler/GC_ObjectPool.h"

void UGC_ObjectPool::AddObjectToPool(UObject* addedObject)
{
	usedObjects.Add(addedObject);
}
