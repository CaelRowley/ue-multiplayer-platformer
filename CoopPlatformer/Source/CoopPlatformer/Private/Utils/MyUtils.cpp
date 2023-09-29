// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/MyUtils.h"

MyUtils::MyUtils()
{
}

MyUtils::~MyUtils()
{
}

void MyUtils::PrintDebug(const FString& Message, const FColor Color)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, Color, Message);
	}
}

