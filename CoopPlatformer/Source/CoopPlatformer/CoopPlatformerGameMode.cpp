// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoopPlatformerGameMode.h"
#include "CoopPlatformerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACoopPlatformerGameMode::ACoopPlatformerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ACoopPlatformerGameMode::HostLANGame()
{
	GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void ACoopPlatformerGameMode::JoinLANGame()
{
	APlayerController *PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (PlayerController) 
	{
		PlayerController->ClientTravel("192.168.1.1", TRAVEL_Absolute);
	}
}
