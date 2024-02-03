
#include "GenericClassesDebug/DebugObjects/GC_DebugObjectManager.h"
#include "GenericClassesMinimals.h"
#include "UObject/ConstructorHelpers.h"
#include "AssetToolsModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "Factories/BlueprintFactory.h"
#include "UObject/SavePackage.h"
#include <Factories/DataAssetFactory.h>

const FString DEBBUG_OBJECTS_DATATABLE_PATH = FString(TEXT("/Game/DebugObjects/DT_DebugObjects"));
const FString DEBBUG_OBJECTS_DATATABLE_PATH_REFERENCE = FString(TEXT("/Script/Engine.DataTable'/Game/DebugObjects/DT_DebugObjects.DT_DebugObjects'"));

void UGC_DebugObjectManager::InitializeDebugObjects()
{
	const UGC_DebugObjectDataAsset* componentsDataAsset = Cast<UGC_DebugObjectDataAsset>(StaticLoadObject(UGC_DebugObjectDataAsset::StaticClass(), NULL, *DEBBUG_OBJECTS_DATATABLE_PATH_REFERENCE));
	if (componentsDataAsset == nullptr)
	{
		CreateDebugObjectsDataTable();
		InitializeDebugObjects();
		return;
	}

	for (TSubclassOf<UGC_DebugObject> debugObjectClassIt : componentsDataAsset->enabledDebugObjects)
	{
		AddDebugObject(debugObjectClassIt);
	}
}

void UGC_DebugObjectManager::AddDebugObject(TSubclassOf<UGC_DebugObject> debugObjectClass)
{
	UGC_DebugObject* debugObject = debugObjectClass->GetDefaultObject<UGC_DebugObject>();
	if (debugObject == nullptr)
	{
		UGC_DebugSystem* debugSystem = UGC_SingletonRegister::GetInstance<UGC_DebugSystem>();
		debugSystem->SendLog(TEXT("Trying to register invalid Debug Object Class"));
		return;
	}

	FString debugCategory;
	debugObjectClass->GetName(debugCategory);
	if (registeredDebugObjects.Contains(debugCategory))
	{
		return;
	}

	registeredDebugObjects.Add(debugCategory);
	if (mainDebugObject == nullptr)
	{
		mainDebugObject = debugObject;
	}
}

void UGC_DebugObjectManager::EnableDebugObject(FString debugObject)
{
	if (debugObject.Contains(debugObject))
	{
		mainDebugObject = registeredDebugObjects[debugObject];
	}
}

UGC_DebugObject* UGC_DebugObjectManager::GetMainDebugObject()
{
	return mainDebugObject;
}

void UGC_DebugObjectManager::CreateDebugObjectsDataTable()
{
	// Load necessary modules
	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	// Generate a unique asset name
	FString Name, PackageName;
	AssetToolsModule.Get().CreateUniqueAssetName(DEBBUG_OBJECTS_DATATABLE_PATH, TEXT(""), PackageName, Name);
	const FString PackagePath = FPackageName::GetLongPackagePath(PackageName);

	// Create object and package
	UPackage* package = CreatePackage(*PackageName);
	UDataAssetFactory* dataAssetFactory = NewObject<UDataAssetFactory >(UDataAssetFactory::StaticClass()); // Can omit, and a default factory will be used
	dataAssetFactory->DataAssetClass = UGC_DebugObjectDataAsset::StaticClass();
	UObject* createdDatatable = AssetToolsModule.Get().CreateAsset(Name, PackagePath, UGC_DebugObjectDataAsset::StaticClass(), dataAssetFactory);
	FSavePackageArgs saveArgs = FSavePackageArgs();
	UPackage::Save(package, createdDatatable, *FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension()), saveArgs);

	// Inform asset registry
	AssetRegistry.AssetCreated(createdDatatable);

	// Tell content browser to show the newly created asset
	TArray<UObject*> Objects;
	Objects.Add(createdDatatable);
	ContentBrowserModule.Get().SyncBrowserToAssets(Objects);
}

void UGC_DebugObjectManager::OnInstanceCreated_Implementation(FDataTableRowHandle singletonDataHandle)
{
	InitializeDebugObjects();
}
