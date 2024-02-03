// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClassesEditor/EditorComponent/GC_EditorComponent.h"

// Sets default values for this component's properties
UGC_EditorComponent::UGC_EditorComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

bool UGC_EditorComponent::IsValidComponent(AActor* componentOwner) const
{
	if (componentOwner)
	{
		return  true;
	}

	return false;
}