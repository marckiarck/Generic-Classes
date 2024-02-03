// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GC_DataTable.generated.h"


USTRUCT(BlueprintType)
struct GENERICCLASSES_API FGC_DataTableRowHandle
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = DatatableRowHandle)
		UObject* aditionalData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = DatatableRowHandle)
		FDataTableRowHandle dataatableRowHandle;

};

UCLASS(BlueprintType)
class UGC_DataTable : public UDataTable
{
	GENERATED_BODY()

};