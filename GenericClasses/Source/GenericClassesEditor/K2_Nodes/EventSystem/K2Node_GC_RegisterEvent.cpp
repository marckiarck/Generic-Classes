// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClassesEditor/K2_Nodes/EventSystem/K2Node_GC_RegisterEvent.h"
#include "Internationalization/Internationalization.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EdGraphSchema_K2.h"
#include "EventSystem/GC_EventBlueprintFunctionLibrary.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "K2Node_CustomEvent.h"

FText UK2Node_GC_RegisterEvent::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("RegisterEvent"));
}

FText UK2Node_GC_RegisterEvent::GetTooltipText() const
{
	return FText::FromString(TEXT("Register a event of the received event type"));
}

FText UK2Node_GC_RegisterEvent::GetMenuCategory() const
{
	return FText::FromString(TEXT("EventRegister"));
}

UFunction* UK2Node_GC_RegisterEvent::GetMainNodeFuntion()
{
	UClass* eventLibraryClass = UGC_EventBlueprintFunctionLibrary::StaticClass();
	return eventLibraryClass->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UGC_EventBlueprintFunctionLibrary, RegisterEvent));
}

