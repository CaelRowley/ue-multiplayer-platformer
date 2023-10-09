// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class COOPPLATFORMER_API MyUtils
{
public:
	MyUtils();
	~MyUtils();

	static void PrintDebug(const FString& Message, const FColor Color = FColor::White);
};
