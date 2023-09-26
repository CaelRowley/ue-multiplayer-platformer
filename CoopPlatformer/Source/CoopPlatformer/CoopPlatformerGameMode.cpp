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
