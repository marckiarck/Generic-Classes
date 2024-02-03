// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GC_EditorComponent.h"
#include "GC_EditorComponentRow.generated.h"

USTRUCT()
struct FGC_EditorComponentData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, DisplayName="Editor Component Class")
	TSubclassOf<UGC_EditorComponent> editorComponentClass;

	UPROPERTY(EditAnywhere, DisplayName="Load Editor Component?")
	bool load = true;
};

UCLASS()
class GENERICCLASSESEDITOR_API UGC_EditorComponentRow : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, DisplayName="Editor Components")
	TArray<FGC_EditorComponentData> editorComponents;
};
