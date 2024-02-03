// Fill out your copyright notice in the Description page of Project Settings.

#if WITH_GAMEPLAY_DEBUGGER

#include "GenericClassesDebug/GameplayDebugger/GC_EventSystemDebuggerCategory.h"
#include "GenericClasses/Public/GenericClassesMinimals.h"


FGC_EventSystemDebuggerCategory::FGC_EventSystemDebuggerCategory()
{
    bShowOnlyWithDebugActor = false;
}

void FGC_EventSystemDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
    UGC_EventRegister* eventRegister = UGC_SingletonRegister::GetInstance<UGC_EventRegister>();
    if (eventRegister)
    {
        launchedEvents = eventRegister->GetLaunchedEvents();
        queuedEvents = eventRegister->GetQueuedEvents();
    }

}

void FGC_EventSystemDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
    CanvasContext.Printf(TEXT("{Yellow}[ Launched Events ]"));
    for (const UGC_Event* launchedEvent : launchedEvents)
    {
        CanvasContext.Printf(TEXT("{Yellow}%s"), *launchedEvent->GetName());
    }
    CanvasContext.Printf(TEXT("{Yellow}"));

    CanvasContext.Printf(TEXT("{Green}[ Queued Events ]"));
    for (const UGC_Event* queuedEvent : queuedEvents)
    {
        CanvasContext.Printf(TEXT("{Green}%s"), *queuedEvent->GetName());
    }
}

TSharedRef<FGameplayDebuggerCategory> FGC_EventSystemDebuggerCategory::MakeInstance()
{
    return MakeShareable(new FGC_EventSystemDebuggerCategory());
}

#endif // WITH_GAMEPLAY_DEBUGGER