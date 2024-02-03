// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GC_Wrapper.generated.h"

UCLASS()
class GENERICCLASSES_API UGC_integerWrapper : public UObject
{
	GENERATED_BODY()

public:
	UGC_integerWrapper();

	UGC_integerWrapper(int initialVariableValue);

	~UGC_integerWrapper();

private:
	int wrappedVariable;

public:
	int Get();

	void Set(int newVariableValue);
};

#define DEFINE_WRAPPED_CLASS(PRIMITIVE_TYPE) \
UCLASS() \
class GENERICCLASSES_API UGC_##PRIMITIVE_TYPEWrapper : public UObject \
{ \
	GENERATED_BODY() \
public: \
	UGC_##PRIMITIVE_TYPEWrapper() \
	{ \
	}; \
 \
	UGC_##PRIMITIVE_TYPEWrapper(PRIMITIVE_TYPE initialVariableValue) : wrappedVariable(initialVariableValue) \
	{ \
	}; \
 \
	~UGC_##PRIMITIVE_TYPEWrapper() \
	{ \
	}; \
 \
private: \
	PRIMITIVE_TYPE wrappedVariable; \
 \
public: \
	PRIMITIVE_TYPE Get() \
	{ \
		return wrappedVariable; \
	}; \
 \
	void Set(PRIMITIVE_TYPE newVariableValue) \
	{ \
		wrappedVariable = newVariableValue; \
	}; \
}; \

//DEFINE_WRAPPED_CLASS(float);
//DEFINE_WRAPPED_CLASS(bool);