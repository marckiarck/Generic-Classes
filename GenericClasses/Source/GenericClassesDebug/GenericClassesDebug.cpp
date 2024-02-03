// Copyright Epic Games, Inc. All Rights Reserved.

#include "GenericClassesDebug.h"

#if WITH_GAMEPLAY_DEBUGGER

#include "GameplayDebugger/GC_EventSystemDebuggerCategory.h"
#include "GameplayDebugger.h"
#include "GameplayDebugger/SingletonRegister/GC_SingletonRegisterCategory.h"
#include "GameplayDebugger/ObjectPooler/GC_ObjectPoolerDebuggerCategory.h"
#include "GameplayDebugger/DebugObjects/GC_DebugObjectCategory.h"

#endif //WITH_GAMEPLAY_DEBUGGER

#define LOCTEXT_NAMESPACE "FGenericClassesDebugModule"

void FGenericClassesDebugModule::StartupModule()
{
#if WITH_GAMEPLAY_DEBUGGER
	IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();

	GameplayDebuggerModule.RegisterCategory("DebugObject", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGC_DebugObjectCategory::MakeInstance),
		EGameplayDebuggerCategoryState::EnabledInGameAndSimulate);
	GameplayDebuggerModule.RegisterCategory("EventSystem", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGC_EventSystemDebuggerCategory::MakeInstance),
		EGameplayDebuggerCategoryState::EnabledInGameAndSimulate);
	GameplayDebuggerModule.RegisterCategory("Singleton", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGC_SingletonRegisterCategory::MakeInstance),
		EGameplayDebuggerCategoryState::EnabledInGameAndSimulate);
	GameplayDebuggerModule.RegisterCategory("ObjectPooler", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGC_ObjectPoolerDebuggerCategory::MakeInstance),
		EGameplayDebuggerCategoryState::EnabledInGameAndSimulate);
	GameplayDebuggerModule.NotifyCategoriesChanged();
#endif //WITH_GAMEPLAY_DEBUGGER

}

void FGenericClassesDebugModule::ShutdownModule()
{
#if WITH_GAMEPLAY_DEBUGGER
	IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
	GameplayDebuggerModule.UnregisterCategory(TEXT("DebugObject"));
	GameplayDebuggerModule.UnregisterCategory(TEXT("EventSystem"));
	GameplayDebuggerModule.UnregisterCategory(TEXT("Singleton"));
	GameplayDebuggerModule.UnregisterCategory(TEXT("ObjectPooler"));
#endif //WITH_GAMEPLAY_DEBUGGER

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGenericClassesDebugModule, GenericClassesDebug)