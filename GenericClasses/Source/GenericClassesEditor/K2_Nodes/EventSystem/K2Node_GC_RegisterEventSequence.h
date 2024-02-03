// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericClassesEditor/K2_Nodes/K2Node_GC_BaseNode.h"
#include "K2Node_GC_RegisterEventSequence.generated.h"


UCLASS()
class GENERICCLASSESEDITOR_API UK2Node_GC_RegisterEventSequence : public UK2Node_GC_BaseNode
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual FText GetMenuCategory() const override;
	
protected:
	UFunction* GetMainNodeFuntion() override;

};
