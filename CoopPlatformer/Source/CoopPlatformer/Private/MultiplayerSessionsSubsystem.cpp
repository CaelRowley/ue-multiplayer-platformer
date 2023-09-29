// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"

#include "Utils/MyUtils.h"

UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
{
	MyUtils::PrintDebug("MSS Constructor"), FColor::Cyan;
}

void UMultiplayerSessionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	MyUtils::PrintDebug("MSS Initialize"), FColor::Cyan;
}

void UMultiplayerSessionsSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("MSS Deinitialize"));
}
