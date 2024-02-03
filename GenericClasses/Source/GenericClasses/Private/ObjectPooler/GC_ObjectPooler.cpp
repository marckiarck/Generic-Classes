// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/ObjectPooler/GC_ObjectPooler.h"


void UGC_ObjectPooler::CreateObject(TSubclassOf<UObject> objectClass, UObject*& createdObject, FDataTableRowHandle creationDataHandle)
{
	createdObject = nullptr;

	if (objectClass == nullptr)
	{
		ensureMsgf(false, TEXT("Trying to instance a nullptr class"));
		return;
	}

	if (objectClass->HasAnyClassFlags(CLASS_Abstract))
	{
		ensureMsgf(false, TEXT("Trying to instance an abstract class"));
		return;
	}

	FName poolKey = GetPoolKey(objectClass);
	if (poolsMap.Contains(poolKey))
	{
		UGC_ObjectPool* pool = poolsMap[poolKey];
		createdObject = pool->GetObjectFromPool<UObject>();

		if (createdObject == nullptr)
		{
			createdObject = NewObject<UObject>(this, objectClass);
			pool->AddObjectToPool(createdObject);
		}

	}
	else
	{
		UGC_ObjectPool* newPool = NewObject<UGC_ObjectPool>();
		createdObject = NewObject<UObject>(this, objectClass);
		poolsMap.Add(poolKey, newPool);
		newPool->AddObjectToPool(createdObject);
	}

	OnPooledObjectCreated<UObject>(createdObject, creationDataHandle);

	ensureMsgf(createdObject, TEXT("Something went wrong during object creation"));
}

void UGC_ObjectPooler::DestroyObject(UObject* objectReference)
{
	if (objectReference == nullptr)
	{
		return;
	}

	OnPooledObjectDestroyed<UObject>(objectReference);

	FName poolKey = GetPoolKey(objectReference->GetClass());
	if (poolsMap.Contains(poolKey))
	{
		UGC_ObjectPool* pool = poolsMap[poolKey];
		pool->RemoveObjectFromPool<UObject>(objectReference);
	}
	else
	{
		if (objectReference->IsValidLowLevel())
		{
			objectReference->BeginDestroy();
		}
	}
}

void UGC_ObjectPooler::SpawnActor(ULevel* spawnLevel, TSubclassOf<AActor> actorClass, FTransform spawnTransForm, FDataTableRowHandle creationDataHandle, AActor*& spawnedActor, bool collisionEnabled)
{
	spawnedActor = nullptr;

	if (actorClass == nullptr)
	{
		ensureMsgf(false, TEXT("Trying to instance a nullptr class"));
		return;
	}

	if (actorClass->HasAnyClassFlags(CLASS_Abstract))
	{
		ensureMsgf(false, TEXT("Trying to instance an abstract class"));
		return;
	}

	UWorld* spawnWorld = spawnLevel->OwningWorld;
	if (spawnWorld == nullptr)
	{
		return;
	}

	FName poolKey = GetPoolKey(actorClass);
	if (poolsMap.Contains(poolKey))
	{
		UGC_ObjectPool* pool = poolsMap[poolKey];
		spawnedActor = pool->GetObjectFromPool<AActor>();

		if (spawnedActor == nullptr)
		{
			spawnedActor = spawnWorld->SpawnActor<AActor>(actorClass, spawnTransForm);
			pool->AddObjectToPool(spawnedActor);
		}

	}
	else
	{
		UGC_ObjectPool* newPool = NewObject<UGC_ObjectPool>();
		spawnedActor = spawnWorld->SpawnActor<AActor>(actorClass, spawnTransForm);
		poolsMap.Add(poolKey, newPool);
		newPool->AddObjectToPool(spawnedActor);
	}

	spawnedActor->SetActorTransform(spawnTransForm);
	spawnedActor->SetActorHiddenInGame(false);
	spawnedActor->SetActorEnableCollision(collisionEnabled);
	spawnedActor->SetActorTickEnabled(true);
	OnPooledObjectCreated<AActor>(spawnedActor, creationDataHandle);

	ensureMsgf(spawnedActor, TEXT("Something went wrong during object creation"));
}

void UGC_ObjectPooler::DespawnActor(AActor* actorReference)
{
	if (actorReference == nullptr)
	{
		return;
	}

	actorReference->SetActorHiddenInGame(true);
	actorReference->SetActorLocation(FVector(100000.f, 100000.f, 100000.f));
	actorReference->SetActorEnableCollision(false);
	actorReference->SetActorTickEnabled(false);
	OnPooledObjectDestroyed<UObject>(actorReference);

	FName poolKey = GetPoolKey(actorReference->GetClass());
	if (poolsMap.Contains(poolKey))
	{
		UGC_ObjectPool* pool = poolsMap[poolKey];
		pool->RemoveObjectFromPool<AActor>(actorReference);
	}
	else
	{
		if (actorReference->IsValidLowLevel())
		{
			actorReference->Destroy();
		}
	}
}

FOnPooledObjectDestroyed& UGC_ObjectPooler::GetOnPooledObjectDestroyed()
{
	return onPooledObjectDestroyedDelegate;
}

FName UGC_ObjectPooler::GetPoolKey(TSubclassOf<UObject> objectClass)
{
	return FName(objectClass->GetName());
}
