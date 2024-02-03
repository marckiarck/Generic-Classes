// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DataStructures/Queues/GC_TimedQueue.h"

template<typename T>
class GENERICCLASSES_API TGC_EventQueue : public TGC_TimedQueue<T>
{
	
};

