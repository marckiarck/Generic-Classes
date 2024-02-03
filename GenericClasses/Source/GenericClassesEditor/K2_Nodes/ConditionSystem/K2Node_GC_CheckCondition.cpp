// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClassesEditor/K2_Nodes/ConditionSystem/K2Node_GC_CheckCondition.h"
#include "ConditionSystem/GC_ConditionFunctionLibrary.h"

UFunction* UK2Node_GC_CheckCondition::GetMainNodeFuntion()
{
	UClass* eventLibraryClass = UGC_ConditionFunctionLibrary::StaticClass();
	return eventLibraryClass->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UGC_ConditionFunctionLibrary, CheckCondition));
}

FText UK2Node_GC_CheckCondition::GetMenuCategory() const
{
	return FText::FromString(TEXT("CondistionSystem"));
}

FText UK2Node_GC_CheckCondition::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("CheckCondition"));
}

FText UK2Node_GC_CheckCondition::GetTooltipText() const
{
	return FText::FromString(TEXT("Checks if a condition sentence returns true or false"));
}
