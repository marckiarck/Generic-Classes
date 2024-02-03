// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClassesEditor/K2_Nodes/EventSystem/K2Node_GC_DelegateEventTick.h"
#include "GenericClasses/Public/EventSystem/GC_EventBlueprintFunctionLibrary.h"

FText UK2Node_GC_DelegateEventTick::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("DelegateEventTick"));
}

FText UK2Node_GC_DelegateEventTick::GetTooltipText() const
{
	return FText::FromString(TEXT("Delegate Event Tick"));
}

FText UK2Node_GC_DelegateEventTick::GetMenuCategory() const
{
	return FText::FromString(TEXT("EventRegister"));
}

UFunction* UK2Node_GC_DelegateEventTick::GetMainNodeFuntion()
{
	UClass* eventLibraryClass = UGC_EventBlueprintFunctionLibrary::StaticClass();
	return eventLibraryClass->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UGC_EventBlueprintFunctionLibrary, DelegateTickEvent));
}
