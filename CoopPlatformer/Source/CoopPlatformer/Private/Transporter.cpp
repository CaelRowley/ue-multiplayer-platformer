// Fill out your copyright notice in the Description page of Project Settings.


#include "Transporter.h"

#include "PressurePlate.h"
#include "CollectableKey.h"
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
			PressurePlateActor->OnActivated.AddDynamic(this, &UTransporter::OnTriggerActorActivated);
			PressurePlateActor->OnDeactivated.AddDynamic(this, &UTransporter::OnTriggerActorDeactivated);
		}

		ACollectableKey* CollectableKeyActor = Cast<ACollectableKey>(TA);
		if (CollectableKeyActor)
		{
			CollectableKeyActor->OnCollected.AddDynamic(this, &UTransporter::OnTriggerActorActivated);
		}
	}
}

void UTransporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AllTriggerActorsTriggered = (ActivatedTriggerCount >= TriggerActors.Num());

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

void UTransporter::OnTriggerActorActivated()
{
	ActivatedTriggerCount++;
	MyUtils::PrintDebug(FString::Printf(TEXT("Transporter Activated: %d"), ActivatedTriggerCount));
}

void UTransporter::OnTriggerActorDeactivated()
{
	ActivatedTriggerCount--;
	MyUtils::PrintDebug(FString::Printf(TEXT("Transporter Activated: %d"), ActivatedTriggerCount));
}
