// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class GC_EventFactory
{
public:
	static class UGC_Event* BuildWaitDelayEvent(float waitTime);
};
