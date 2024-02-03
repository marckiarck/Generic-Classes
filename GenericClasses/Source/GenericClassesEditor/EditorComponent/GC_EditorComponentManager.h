// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GC_EditorComponent.h"
#include "Engine/DataTable.h"
#include "SingletonRegister/GC_Singleton.h"
#include "GC_EditorComponentManager.generated.h"


UCLASS()
class GENERICCLASSESEDITOR_API UGC_EditorComponentManager : public UObject, public IGC_Singleton
{
	GENERATED_BODY()

public:

	UGC_EditorComponentManager();

	void RegisterEditorComponent(TSubclassOf<UGC_EditorComponent> componentClass);

protected:
	void OnInstanceCreated_Implementation(FDataTableRowHandle singletonDataHandle) override;

private:
	UPROPERTY(Transient)
	TArray<UGC_EditorComponent*> registeredEditorComponents;

	void CreateEditorComponentDataTable();

	void LoadEditorComponents(const class UGC_EditorComponentRow* componentsDatatable);

	UFUNCTION()
	void OnActorSelectionChanges(const TArray<UObject*>& selectedObjects, bool forceRefresh);

};
