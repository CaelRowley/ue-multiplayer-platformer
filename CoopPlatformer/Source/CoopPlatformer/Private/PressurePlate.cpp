// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

#include "Utils/MyUtils.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	Activated = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerMesh"));
	TriggerMesh->SetupAttachment(RootComp);
	TriggerMesh->SetIsReplicated(true);

	auto TriggerMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (TriggerMeshAsset.Succeeded())
	{
		TriggerMesh->SetStaticMesh(TriggerMeshAsset.Object);
		TriggerMesh->SetRelativeScale3D(FVector(3.3f, 3.3f, 0.2f));
		TriggerMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
	}

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Stylized_Egypt/Meshes/building/SM_building_part_08.SM_building_part_08"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
		Mesh->SetRelativeScale3D(FVector(4.0f, 4.0f, 0.5f));
		Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 7.2f));
	}

	TravelDistance = 10.0f;
	TravelTime = 0.05f;
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	TriggerMesh->SetVisibility(false);
	TriggerMesh->SetCollisionProfileName(FName("OverlapAll"));

	StartPoint = GetActorLocation();
	EndPoint = GetActorLocation() - FVector(0.0f, 0.0f, TravelDistance);
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HasAuthority())
	{
		TArray<AActor*> OverlappingActors;
		AActor* TriggerActor = 0;
		TriggerMesh->GetOverlappingActors(OverlappingActors);

		for (int i = 0; i < OverlappingActors.Num(); ++i)
		{
			AActor* OverlappingActor = OverlappingActors[i];
			if (OverlappingActor->ActorHasTag("TriggerActor"))
			{
				TriggerActor = OverlappingActor;
				break;
			}
			//MyUtils::PrintDebug(FString::Printf(TEXT("Name: %s"), *A->GetName()), FColor::White);
		}

		if (TriggerActor)
		{
			if (!Activated)
			{
				OnActivated.Broadcast();
				Activated = true;
			}
		}
		else
		{
			if (Activated)
			{
				OnDeactivated.Broadcast();
				Activated = false;
			}
		}

		FVector CurrentLocation = GetActorLocation();
		FVector TargetLocation = TriggerActor ? EndPoint : StartPoint;
		float Speed = FVector::Distance(CurrentLocation, TargetLocation) / TravelTime;
		if (!CurrentLocation.Equals(TargetLocation))
		{
			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
			SetActorLocation(NewLocation);
		}
	}
}

