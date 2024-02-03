// Fill out your copyright notice in the Description page of Project Settings.


#include "K2Node_GC_BaseNode.h"
#include "Internationalization/Internationalization.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EdGraphSchema_K2.h"
#include "EventSystem/GC_EventBlueprintFunctionLibrary.h"
#include "EventSystem/GC_EventBlueprintFunctionLibrary.h"
#include "K2Node_CustomEvent.h"

int UK2Node_GC_BaseNode::customEventId = 0;

FText UK2Node_GC_BaseNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("TestNode"));
}

FText UK2Node_GC_BaseNode::GetTooltipText() const
{
	return FText::FromString(TEXT("Test node"));
}

FText UK2Node_GC_BaseNode::GetMenuCategory() const
{
	return FText::FromString(TEXT("TestNode"));
}

void UK2Node_GC_BaseNode::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);
	UClass* Action = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(Action))
	{
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());
		check(Spawner != nullptr);
		ActionRegistrar.AddBlueprintAction(Action, Spawner);
	}
}

void UK2Node_GC_BaseNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	// Execution pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	CreateFunctionParameterPins(GetMainNodeFuntion(), EGPD_Input);

}

void UK2Node_GC_BaseNode::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	UFunction* mainNodeFunction = GetMainNodeFuntion();
	if (!mainNodeFunction)
	{
		CompilerContext.MessageLog.Error(TEXT("The function has not been found."), this);
		return;
	}

	UK2Node_CallFunction* mainCallFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	mainCallFunction->SetFromFunction(mainNodeFunction);
	mainCallFunction->AllocateDefaultPins();
	CompilerContext.MessageLog.NotifyIntermediateObjectCreation(mainCallFunction, this);

	LinkFunctionPins(mainNodeFunction, mainCallFunction, CompilerContext, SourceGraph, K2Schema);

	//Exec pins
	UEdGraphPin* NodeExec = GetExecPin();
	UEdGraphPin* NodeThen = FindPin(UEdGraphSchema_K2::PN_Then);
	UEdGraphPin* InternalExec = mainCallFunction->GetExecPin();
	CompilerContext.MovePinLinksToIntermediate(*NodeExec, *InternalExec);
	UEdGraphPin* InternalThen = mainCallFunction->GetThenPin();
	CompilerContext.MovePinLinksToIntermediate(*NodeThen, *InternalThen);

	//After we are done we break all links to this node (not the internally created one)
	BreakAllNodeLinks();
}

void UK2Node_GC_BaseNode::CreateFunctionParameterPins(UFunction* pinnedFunction, EEdGraphPinDirection pinDirection)
{
	if (pinnedFunction == nullptr)
	{
		ensureMsgf(false, TEXT("Recieved function is nullptr"));
		return;
	}

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	//Function Pins
	TArray<FName> functionParametersArray = GetFunctionParameters(pinnedFunction);
	for (FName parameterNameIt : functionParametersArray)
	{
		FEdGraphPinType pinType;
		FProperty* parameterProperty = FindFProperty<FProperty>(pinnedFunction, parameterNameIt);
		const bool canConvertPinToType = K2Schema->ConvertPropertyToPinType(parameterProperty, pinType);

		if (parameterProperty->HasAnyPropertyFlags(CPF_OutParm))
		{
			CreatePin(EGPD_Output, pinType, parameterNameIt);
		}
		else
		{
			CreatePin(pinDirection, pinType, parameterNameIt);
		}
	}

	//Delgates Pins
	TArray<FName> functionDelegatesArray = GetFunctionDelegates(pinnedFunction);
	int32 pinIndex = 0;
	for (FName delegatesNameIt : functionDelegatesArray)
	{
		CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, delegatesNameIt);

		FDelegateProperty* delegateProperty = pinnedFunction ? FindFProperty<FDelegateProperty>(pinnedFunction, delegatesNameIt) : nullptr;
		UFunction* delegateFunction = delegateProperty ? delegateProperty->SignatureFunction : nullptr;
		CreateFunctionParameterPins(delegateFunction, EGPD_Output);
	}

}

void UK2Node_GC_BaseNode::LinkFunctionPins(UFunction* pinnedFunction, UK2Node_CallFunction* pinnedCallFunction, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	if (!pinnedFunction)
	{
		CompilerContext.MessageLog.Error(TEXT("The function has not been found."), this);
		return;
	}

	LinkFunctionParametersToPins(pinnedFunction, pinnedCallFunction, CompilerContext);
	LinkFunctionDelegatesPins(pinnedFunction, pinnedCallFunction, CompilerContext, SourceGraph, K2Schema);
}

void UK2Node_GC_BaseNode::LinkFunctionParametersToPins(UFunction* pinnedFunction, UK2Node_CallFunction* pinnedCallFunction, FKismetCompilerContext& CompilerContext)
{
	TArray<FName> parametersArray = GetFunctionParameters(pinnedFunction);
	for (FName parameterNameIt : parametersArray)
	{
		CompilerContext.MovePinLinksToIntermediate(*FindPin(parameterNameIt), *pinnedCallFunction->FindPinChecked(parameterNameIt));
	}
}

void UK2Node_GC_BaseNode::LinkFunctionDelegatesPins(UFunction* pinnedFunction, UK2Node_CallFunction* pinnedCallFunction, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema)
{
	
	UEdGraphPin* InternalThen = pinnedCallFunction->GetThenPin();
	TArray<FName> delegatesArray = GetFunctionDelegates(pinnedFunction);
	for (FName delegateNameIt : delegatesArray)
	{

		//Create event node
		UK2Node_CustomEvent* pinnedFunctionDelegateEventNode = CompilerContext.SpawnIntermediateEventNode<UK2Node_CustomEvent>(this, pinnedCallFunction->FindPin(delegateNameIt), SourceGraph);
		FString eventId = FString::FromInt(++customEventId);
		FName customEventName = delegateNameIt;
		customEventName.AppendString(eventId);
		pinnedFunctionDelegateEventNode->CustomFunctionName = *eventId;
		pinnedFunctionDelegateEventNode->AllocateDefaultPins();

		//Assign onEventFinish pin to event node
		UEdGraphPin* mainCallFunctionDelegatePin = pinnedCallFunction->FindPin(delegateNameIt);
		UEdGraphPin* eventDelegatePin = pinnedFunctionDelegateEventNode->FindPin(UK2Node_CustomEvent::DelegateOutputName);
		K2Schema->TryCreateConnection(mainCallFunctionDelegatePin, eventDelegatePin);

		// Connect delegate node to OnEventFinish pin
		UEdGraphPin* outputCompletedPin = FindPin(delegateNameIt);
		UEdGraphPin* assignOutputExePin = pinnedFunctionDelegateEventNode->FindPin(UEdGraphSchema_K2::PN_Then);
		CompilerContext.MovePinLinksToIntermediate(*outputCompletedPin, *assignOutputExePin).CanSafeConnect();

		//Create pins for the delegate parameter
		FDelegateProperty* onDelegateProperty = pinnedFunction ? FindFProperty<FDelegateProperty>(pinnedFunction, delegateNameIt) : nullptr;
		UFunction* onDelegateSignature = onDelegateProperty ? onDelegateProperty->SignatureFunction : nullptr;
		for (TFieldIterator<FProperty> delegateParameterIt(onDelegateSignature); delegateParameterIt && (delegateParameterIt->PropertyFlags & CPF_Parm); ++delegateParameterIt)
		{
			const FProperty* param = *delegateParameterIt;
			if (!param->HasAnyPropertyFlags(CPF_OutParm) || param->HasAnyPropertyFlags(CPF_ReferenceParm))
			{

				FEdGraphPinType pinType;
				const bool canConvertPinToType = K2Schema->ConvertPropertyToPinType(param, /*out*/ pinType);
				const bool canCreateUserDefinedPin = (nullptr != pinnedFunctionDelegateEventNode->CreateUserDefinedPin(param->GetFName(), pinType, EGPD_Output));

				UEdGraphPin* eventPin = pinnedFunctionDelegateEventNode->FindPinChecked(param->GetFName());
				UEdGraphPin* nodePin = FindPinChecked(param->GetFName());
				CompilerContext.MovePinLinksToIntermediate(*nodePin, *eventPin);
			}
		}
	}
}

UFunction* UK2Node_GC_BaseNode::GetMainNodeFuntion()
{
	UClass* eventLibraryClass = UGC_EventBlueprintFunctionLibrary::StaticClass();
	return eventLibraryClass->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UGC_EventBlueprintFunctionLibrary, TestFunction));
}

TArray<FName> UK2Node_GC_BaseNode::GetFunctionParameters(UFunction* functionPtr)
{
	TArray<FName> returnedArray;
	for (TFieldIterator<FProperty> parameterIt(functionPtr); parameterIt && (parameterIt->PropertyFlags & CPF_Parm); ++parameterIt)
	{
		FProperty* parameter = *parameterIt;
		FName parameterName = parameter->GetFName();
		if (FindFProperty<FDelegateProperty>(functionPtr, parameterName) == nullptr)
		{
			returnedArray.Add(parameterName);
		}
	}

	return returnedArray;
}

TArray<FName> UK2Node_GC_BaseNode::GetFunctionDelegates(UFunction* functionPtr)
{

	TArray<FName> returnedArray;
	for (TFieldIterator<FProperty> parameterIt(functionPtr); parameterIt && (parameterIt->PropertyFlags & CPF_Parm); ++parameterIt)
	{
		FProperty* parameter = *parameterIt;
		FName parameterName = parameter->GetFName();
		if (FindFProperty<FDelegateProperty>(functionPtr, parameterName))
		{
			returnedArray.Add(parameterName);
		}
	}

	return returnedArray;
}
