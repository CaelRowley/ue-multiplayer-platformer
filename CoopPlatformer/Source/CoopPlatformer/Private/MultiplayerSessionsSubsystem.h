// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "MultiplayerSessionsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UMultiplayerSessionsSubsystem();

	IOnlineSessionPtr SessionInterface;
	
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void CreateServer(FString ServerName);
	UFUNCTION(BlueprintCallable)
	void FindServer(FString ServerName);

	void OnCreateSessionComplete(FName SessionName, bool WasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool WasSuccessful);
	void OnFindSessionsComplete(bool WasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	bool CreateServerAfterDestroy;
	FString DestroyServerName;
	FString ServerNameToFind;
	FName MySessionName;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
