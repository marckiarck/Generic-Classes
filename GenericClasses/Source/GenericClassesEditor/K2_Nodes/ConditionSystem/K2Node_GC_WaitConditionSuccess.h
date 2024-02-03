// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericClassesEditor/K2_Nodes/K2Node_GC_BaseNode.h"
#include "K2Node_GC_WaitConditionSuccess.generated.h"

/**
 * 
 */
UCLASS()
class GENERICCLASSESEDITOR_API UK2Node_GC_WaitConditionSuccess : public UK2Node_GC_BaseNode
{
	GENERATED_BODY()
	
protected:

	UFunction* GetMainNodeFuntion() override;

public:

	FText GetMenuCategory() const override;
	FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	FText GetTooltipText() const override;

};
