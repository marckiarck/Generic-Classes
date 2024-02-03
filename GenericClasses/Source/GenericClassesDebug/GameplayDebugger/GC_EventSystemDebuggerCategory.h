// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_GAMEPLAY_DEBUGGER

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"


class GENERICCLASSESDEBUG_API FGC_EventSystemDebuggerCategory : public FGameplayDebuggerCategory
{
private:
	TArray<const class UGC_Event*> launchedEvents;
	TArray<const class UGC_Event*> queuedEvents;

public:
	FGC_EventSystemDebuggerCategory();

	void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();
};

#endif // WITH_GAMEPLAY_DEBUGGER