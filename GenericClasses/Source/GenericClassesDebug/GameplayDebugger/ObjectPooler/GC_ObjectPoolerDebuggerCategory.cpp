// Fill out your copyright notice in the Description page of Project Settings.

#if WITH_GAMEPLAY_DEBUGGER

#include "GenericClassesDebug/GameplayDebugger/ObjectPooler/GC_ObjectPoolerDebuggerCategory.h"
#include "GenericClasses/Public/GenericClassesMinimals.h"
#include "ObjectPooler/GC_ObjectPooler.h"
#include "ObjectPooler/GC_ObjectPool.h"


FGC_ObjectPoolerDebuggerCategory::FGC_ObjectPoolerDebuggerCategory()
{
    bShowOnlyWithDebugActor = false;
}

void FGC_ObjectPoolerDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
    UGC_ObjectPooler* objectPooler = UGC_SingletonRegister::GetInstance<UGC_ObjectPooler>();
    if(objectPooler)
    {
        poolsMap = objectPooler->GetPoolsMap();
    }

}

void FGC_ObjectPoolerDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{

    TArray<FName> keyClasses;

    poolsMap.GetKeys(keyClasses);

    for (FName key : keyClasses)
    {
        UGC_ObjectPool* objPool = poolsMap[key];
        FString className = key.ToString();

        CanvasContext.Printf(TEXT("{White}[%s] {Green}Free: %d {White}| {Yellow}Used: %d"), *className, objPool->GetFreeObjects().Num(), objPool->GetUsedObjects().Num());
    }
}

TSharedRef<FGameplayDebuggerCategory> FGC_ObjectPoolerDebuggerCategory::MakeInstance()
{
    return MakeShareable(new FGC_ObjectPoolerDebuggerCategory());
}

#endif // WITH_GAMEPLAY_DEBUGGER