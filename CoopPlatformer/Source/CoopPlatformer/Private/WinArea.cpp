// Fill out your copyright notice in the Description page of Project Settings.
#include "../CoopPlatformerCharacter.h"
#include "Utils/MyUtils.h"

#include "WinArea.h"

AWinArea::AWinArea()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	WinAreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WinAreaBox"));
	SetRootComponent(WinAreaBox);

	WinCondition = false;
}

void AWinArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWinArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (!WinCondition)
		{
			TArray<AActor*> OverlapActors;
			WinAreaBox->GetOverlappingActors(OverlapActors, ACoopPlatformerCharacter::StaticClass());

			WinCondition = (OverlapActors.Num() == 2);
			if (WinCondition)
			{
				MyUtils::PrintDebug(TEXT("WINNER WINNER CHICKEN DINNER!"));
			}
		}
	}
}

