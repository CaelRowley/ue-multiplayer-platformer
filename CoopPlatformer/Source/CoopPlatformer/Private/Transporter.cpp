// Fill out your copyright notice in the Description page of Project Settings.


#include "Transporter.h"

#include "PressurePlate.h"
#include "Utils/MyUtils.h"

UTransporter::UTransporter()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);

	MoveTime = 3.0f;
	ActivatedTriggerCount = 0;
	AllTriggerActorsTriggered = false;

	ArePointsSet = false;
	StartPoint = FVector::Zero();
	EndPoint = FVector::Zero();
}

void UTransporter::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* TA : TriggerActors)
	{
		APressurePlate* PressurePlateActor = Cast<APressurePlate>(TA);
		if (PressurePlateActor)
		{
			PressurePlateActor->OnActivated.AddDynamic(this, &UTransporter::OnPressurePlateActivated);
			PressurePlateActor->OnDeactivated.AddDynamic(this, &UTransporter::OnPressurePlateDeactivated);
		}
	}
}

void UTransporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerActors.Num() > 0)
	{
		AllTriggerActorsTriggered = (ActivatedTriggerCount >= TriggerActors.Num());
		if (AllTriggerActorsTriggered)
		{
			MyUtils::PrintDebug(FString("AllTriggerActorsTriggered!"));
		}
	}

	AActor* MyOwner = GetOwner();
	if (MyOwner && MyOwner->HasAuthority() && ArePointsSet)
	{
		FVector CurrentLocation = MyOwner->GetActorLocation();
		float Speed = FVector::Distance(StartPoint, EndPoint) / MoveTime;

		FVector TargetLocation = AllTriggerActorsTriggered ? EndPoint : StartPoint;
		if (!CurrentLocation.Equals(TargetLocation))
		{
			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
			MyOwner->SetActorLocation(NewLocation);
		}
	}
}

void UTransporter::SetPoints(FVector NewStartPoint, FVector NewEndPoint)
{
	StartPoint = NewStartPoint;
	EndPoint = NewEndPoint;
	ArePointsSet = true;
}

void UTransporter::OnPressurePlateActivated()
{
	ActivatedTriggerCount++;
	MyUtils::PrintDebug(FString::Printf(TEXT("Transporter Activated: %d"), ActivatedTriggerCount));
}

void UTransporter::OnPressurePlateDeactivated()
{
	ActivatedTriggerCount--;
	MyUtils::PrintDebug(FString::Printf(TEXT("Transporter Activated: %d"), ActivatedTriggerCount));
}
