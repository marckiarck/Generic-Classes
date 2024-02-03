// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "K2Node_GC_BaseNode.generated.h"


UCLASS()
class GENERICCLASSESEDITOR_API UK2Node_GC_BaseNode : public UK2Node
{
	GENERATED_BODY()
	
private:
	static int customEventId;

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual FText GetMenuCategory() const override;

	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;

protected:
	void CreateFunctionParameterPins(UFunction* pinnedFunction, EEdGraphPinDirection pinDirection);

	void LinkFunctionPins(UFunction* pinnedFunction, UK2Node_CallFunction* pinnedCallFunction, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema);
	void LinkFunctionParametersToPins(UFunction* pinnedFunction, UK2Node_CallFunction* pinnedCallFunction, FKismetCompilerContext& CompilerContext);
	void LinkFunctionDelegatesPins(UFunction* pinnedFunction, UK2Node_CallFunction* pinnedCallFunction, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema);

	virtual UFunction* GetMainNodeFuntion();
	TArray<FName> GetFunctionParameters(UFunction* functionPtr);
	TArray<FName> GetFunctionDelegates(UFunction* functionPtr);
};
