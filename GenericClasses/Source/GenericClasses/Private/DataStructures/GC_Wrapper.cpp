// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/DataStructures/GC_Wrapper.h"


UGC_integerWrapper::UGC_integerWrapper()
{

}

UGC_integerWrapper::UGC_integerWrapper(int initialVariableValue) : wrappedVariable(initialVariableValue)
{

}

UGC_integerWrapper::~UGC_integerWrapper()
{

}

int UGC_integerWrapper::Get()
{
	return wrappedVariable;
}

void UGC_integerWrapper::Set(int newVariableValue)
{
	wrappedVariable = newVariableValue;
}
