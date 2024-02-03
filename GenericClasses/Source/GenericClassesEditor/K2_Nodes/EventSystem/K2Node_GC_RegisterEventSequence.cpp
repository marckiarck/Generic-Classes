// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClassesEditor/K2_Nodes/EventSystem/K2Node_GC_RegisterEventSequence.h"
#include "GenericClasses/Public/EventSystem/GC_EventBlueprintFunctionLibrary.h"

FText UK2Node_GC_RegisterEventSequence::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("RegisterEventSequence"));
}

FText UK2Node_GC_RegisterEventSequence::GetTooltipText() const
{
	return FText::FromString(TEXT("Registers an EventSequence based on the input pins"));
}

FText UK2Node_GC_RegisterEventSequence::GetMenuCategory() const
{
	return FText::FromString(TEXT("EventRegister"));
}

UFunction* UK2Node_GC_RegisterEventSequence::GetMainNodeFuntion()
{
	UClass* eventLibraryClass = UGC_EventBlueprintFunctionLibrary::StaticClass();
	return eventLibraryClass->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UGC_EventBlueprintFunctionLibrary, RegisterEventSequence));
}
