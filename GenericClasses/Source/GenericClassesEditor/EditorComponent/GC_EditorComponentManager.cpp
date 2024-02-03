// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClassesEditor/EditorComponent/GC_EditorComponentManager.h"
#include "GC_EditorComponentRow.h"
#include "Kismet2/ComponentEditorUtils.h"
#include "LevelEditor.h"
#include "UObject/ConstructorHelpers.h"
#include "AssetToolsModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "Factories/BlueprintFactory.h"
#include "Factories/DataTableFactory.h"
#include "Factories/DataAssetFactory.h"
#include "UObject/SavePackage.h"


const FString COMPONENTS_DATATABLE_PATH = FString(TEXT("/Game/EditorComponent/DT_EditorComponents"));
const FString COMPONENTS_DATATABLE_PATH_REFERENCE = FString(TEXT("/Script/Engine.DataTable'/Game/EditorComponent/DT_EditorComponents.DT_EditorComponents'"));

UGC_EditorComponentManager::UGC_EditorComponentManager()
{
	FLevelEditorModule& levelEditor = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
	levelEditor.OnActorSelectionChanged().AddUObject(this, &UGC_EditorComponentManager::OnActorSelectionChanges);
}

void UGC_EditorComponentManager::RegisterEditorComponent(TSubclassOf<UGC_EditorComponent> componentClass)
{
	registeredEditorComponents.AddUnique(componentClass.GetDefaultObject());
}

void UGC_EditorComponentManager::CreateEditorComponentDataTable()
{
	// Load necessary modules
	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	// Generate a unique asset name
	FString Name, PackageName;
	AssetToolsModule.Get().CreateUniqueAssetName(COMPONENTS_DATATABLE_PATH, TEXT(""), PackageName, Name);
	const FString PackagePath = FPackageName::GetLongPackagePath(PackageName);

	// Create object and package
	UPackage* package = CreatePackage(*PackageName);
	UDataAssetFactory* dataAssetFactory = NewObject<UDataAssetFactory >(UDataAssetFactory::StaticClass()); // Can omit, and a default factory will be used
	dataAssetFactory->DataAssetClass = UGC_EditorComponentRow::StaticClass();
	UObject* createdDatatable = AssetToolsModule.Get().CreateAsset(Name, PackagePath, UGC_EditorComponentRow::StaticClass(), dataAssetFactory);
	FSavePackageArgs saveArgs = FSavePackageArgs();
	UPackage::Save(package, createdDatatable, *FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension()), saveArgs);

	// Inform asset registry
	AssetRegistry.AssetCreated(createdDatatable);

	// Tell content browser to show the newly created asset
	TArray<UObject*> Objects;
	Objects.Add(createdDatatable);
	ContentBrowserModule.Get().SyncBrowserToAssets(Objects);
}

void UGC_EditorComponentManager::LoadEditorComponents(const UGC_EditorComponentRow* componentsDatatable)
{

	for (FGC_EditorComponentData editorComponentIt : componentsDatatable->editorComponents)
	{
		if (editorComponentIt.load)
		{
			RegisterEditorComponent(editorComponentIt.editorComponentClass);
		}
	}
}

void UGC_EditorComponentManager::OnActorSelectionChanges(const TArray<UObject*>& selectedObjects, bool forceRefresh)
{
	if (selectedObjects.Num() == 0)
	{
		return;
	}

	const UGC_EditorComponentRow* componentsDataAsset = Cast<UGC_EditorComponentRow>(StaticLoadObject(UGC_EditorComponentRow::StaticClass(), NULL, *COMPONENTS_DATATABLE_PATH_REFERENCE));
	if (componentsDataAsset == nullptr)
	{
		CreateEditorComponentDataTable();
		return;
	}

	LoadEditorComponents(componentsDataAsset);

	for (UObject* selectedObject : selectedObjects)
	{

		if (AActor* selectedActor = Cast<AActor>(selectedObject))
		{
			if (selectedActor->FindComponentByClass<UGC_EditorComponent>() == nullptr)
			{

				for (const UGC_EditorComponent* editorComponent : registeredEditorComponents)
				{
					if (editorComponent->IsValidComponent(selectedActor))
					{

						//Create component
						selectedActor->Modify();
						const FName componentName = *FComponentEditorUtils::GenerateValidVariableName(editorComponent->GetClass(), selectedActor);

						UGC_EditorComponent* unattachedEditorComponent = NewObject<UGC_EditorComponent>(selectedActor, editorComponent->GetClass(), componentName, RF_Transient);
						unattachedEditorComponent->CreationMethod = EComponentCreationMethod::Native;
						unattachedEditorComponent->OnComponentCreated();
						selectedActor->AddInstanceComponent(unattachedEditorComponent);
						unattachedEditorComponent->RegisterComponent();

						//Add component to parent actor's details panel
						//FSCSEditorTreeNodePtrType ParentNodePtr = FindParentForNewComponent(NewInstanceComponent);
						//FSCSEditorTreeNodePtrType parentNodePtr = FSCSEditorTreeNode::FactoryNodeFromComponent(selectedActor->GetRootComponent());
						//parentNodePtr->AddChildFromComponent(unattachedEditorComponent);
						//parentNodePtr->SetObject(selectedActor);

						selectedActor->RerunConstructionScripts();

						FLevelEditorModule& levelEditor = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
						levelEditor.BroadcastComponentsEdited();
						levelEditor.BroadcastRedrawViewports(true); 


					}
				}

			}

		}

	}

}

void UGC_EditorComponentManager::OnInstanceCreated_Implementation(FDataTableRowHandle singletonDataHandle)
{
	
}
