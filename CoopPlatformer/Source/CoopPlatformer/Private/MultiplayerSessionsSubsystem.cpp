// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
 
#include "Utils/MyUtils.h"

UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
{
	MyUtils::PrintDebug("MSS Constructor", FColor::Cyan);
}

void UMultiplayerSessionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	MyUtils::PrintDebug("MSS Initialize", FColor::Cyan);
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem)
	{
		FString SubsystemName = OnlineSubsystem->GetSubsystemName().ToString();
		MyUtils::PrintDebug(SubsystemName);

		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			MyUtils::PrintDebug("SessionInterface is valid");
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerSessionsSubsystem::OnCreateSessionComplete);
		}
	}
}

void UMultiplayerSessionsSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("MSS Deinitialize"));
}

void UMultiplayerSessionsSubsystem::CreateServer(FString ServerName)
{
	if (ServerName.IsEmpty())
	{
		MyUtils::PrintDebug("CreateServer, ServerName cannot be empty!", FColor::Red);
		return;
	}

	FName MySessionName = FName("Multiplayer Platformer");
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.NumPublicConnections = 2;
	SessionSettings.bUseLobbiesIfAvailable = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bAllowJoinViaPresence = true;
	SessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";

	SessionInterface->CreateSession(0, MySessionName, SessionSettings);
}

void UMultiplayerSessionsSubsystem::FindServer(FString ServerName)
{
	MyUtils::PrintDebug("FindServer", FColor::Cyan);
}

void UMultiplayerSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool WasSuccessful)
{
	MyUtils::PrintDebug(FString::Printf(TEXT("OnCreateSessionComplete: %d"), WasSuccessful));

	if (WasSuccessful)
	{
		GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
	}
}
