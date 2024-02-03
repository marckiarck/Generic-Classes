// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericClasses/Public/DebugSystem/GC_DebugSystem.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"


void UGC_DebugSystem::Check(bool checkSentence, FString failMessage)
{
	if (!checkSentence)
	{
		FSlateNotificationManager& slateNotificationManager = FSlateNotificationManager::Get();
		FNotificationInfo notificationInfo = FNotificationInfo(FText::FromString(failMessage));

		slateNotificationManager.AddNotification(notificationInfo);
		//UE_LOG(LogTemp, Warning, failMessage);
	}
	
}

void UGC_DebugSystem::SendLog(FString logMessage)
{
	FSlateNotificationManager& slateNotificationManager = FSlateNotificationManager::Get();
	FNotificationInfo notificationInfo = FNotificationInfo(FText::FromString(logMessage));

	slateNotificationManager.AddNotification(notificationInfo);
}
