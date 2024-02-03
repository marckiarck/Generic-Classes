// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/Characters/Controllers/GC_AIController.h"
#include "BrainComponent.h"

void AGC_AIController::OnPooledObjectCreated(FDataTableRowHandle creationDataHandle)
{
	if (FGC_AIControllerSpawnRow* controllerRow = GetRow<FGC_AIControllerSpawnRow>(creationDataHandle))
	{
		currentBehaviorTree = controllerRow->behaviorTree;
		RunBehaviorTree(currentBehaviorTree);
	}
}

void AGC_AIController::OnPooledObjectDestroyed()
{
	if (UBrainComponent* brainComponent = GetBrainComponent())
	{
		FString stopLogicContext = TEXT("On pooled controller destroyed");
		brainComponent->StopLogic(stopLogicContext);
	}
}
