// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GC_EditorComponent.generated.h"


UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENERICCLASSESEDITOR_API UGC_EditorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGC_EditorComponent();

	virtual bool IsValidComponent(AActor* componentOwner) const;

};
