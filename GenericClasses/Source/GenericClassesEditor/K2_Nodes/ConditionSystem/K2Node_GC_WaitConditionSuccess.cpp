// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClassesEditor/K2_Nodes/ConditionSystem/K2Node_GC_WaitConditionSuccess.h"
#include "ConditionSystem/GC_ConditionFunctionLibrary.h"

UFunction* UK2Node_GC_WaitConditionSuccess::GetMainNodeFuntion()
{
	UClass* eventLibraryClass = UGC_ConditionFunctionLibrary::StaticClass();
	return eventLibraryClass->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UGC_ConditionFunctionLibrary, WaitConditionSuccess));
}

FText UK2Node_GC_WaitConditionSuccess::GetMenuCategory() const
{
	return FText::FromString(TEXT("CondistionSystem"));
}

FText UK2Node_GC_WaitConditionSuccess::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("WaitConditionSuccess"));
}

FText UK2Node_GC_WaitConditionSuccess::GetTooltipText() const
{
	return FText::FromString(TEXT("Wait until condition sentence returns true"));
}
