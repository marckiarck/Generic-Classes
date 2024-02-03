// Copyright Epic Games, Inc. All Rights Reserved.

#include "GenericClassesEditor.h"
#include "SingletonRegister/GC_SingletonRegister.h"
#include "EditorComponent/GC_EditorComponentManager.h"

#define LOCTEXT_NAMESPACE "FGenericClassesEditorModule"

void FGenericClassesEditorModule::StartupModule()
{
	UGC_EditorComponentManager* editorComponentManager = UGC_SingletonRegister::GetInstance<UGC_EditorComponentManager>();
}

void FGenericClassesEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGenericClassesEditorModule, GenericClassesEditor)