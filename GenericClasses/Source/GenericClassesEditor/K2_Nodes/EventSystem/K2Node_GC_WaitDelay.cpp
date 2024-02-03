// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClassesEditor/K2_Nodes/EventSystem/K2Node_GC_WaitDelay.h"
#include "GenericClasses/Public/EventSystem/GC_EventBlueprintFunctionLibrary.h"

FText UK2Node_GC_WaitDelay::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("WaitDelay"));
}

FText UK2Node_GC_WaitDelay::GetTooltipText() const
{
	return FText::FromString(TEXT("Wait delay"));
}

FText UK2Node_GC_WaitDelay::GetMenuCategory() const
{
	return FText::FromString(TEXT("EventRegister"));
}

UFunction* UK2Node_GC_WaitDelay::GetMainNodeFuntion()
{
	UClass* eventLibraryClass = UGC_EventBlueprintFunctionLibrary::StaticClass();
	return eventLibraryClass->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UGC_EventBlueprintFunctionLibrary, WaitDelay));
}
