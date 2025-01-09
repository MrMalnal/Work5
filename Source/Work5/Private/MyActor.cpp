// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh Component"));
	RootComponent = MeshComponent;
	UStaticMesh* Mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object;
	MeshComponent->SetStaticMesh(Mesh);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	ActorPosition = FVector2D(0.0f, 0.0f);
	SetActorLocation(FVector(ActorPosition.X, ActorPosition.Y, 50.0f));
	StartPosition = ActorPosition;
	StepCount = 0;
	EventCount = 0;
	UE_LOG(LogTemp, Warning, TEXT("Start Position : (X:%.0f, Y:%.0f)",ActorPosition.X, ActorPosition.Y));
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StepCount < 10)
	{
		Move();
		if (CreateEvent())
			EventCount++;
		UE_LOG(LogTemp, Warning, TEXT("Step %d : Current Position : %s, EventCount : %d"), StepCount + 1, *ActorPosition.ToString(), EventCount);
		StepCount++;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Total Move Distance : %f, Total EventCount : %d"), CalculationDistance(StartPosition, ActorPosition), EventCount);
		SetActorTickEnabled(false);
	}
}

int32 AMyActor::Step()
{
	return FMath::RandRange(0, 1);
}

void AMyActor::Move()
{
	ActorPosition.X += Step();
	ActorPosition.Y += Step();

	SetActorLocation(FVector(ActorPosition.X, ActorPosition.Y, 50.0f));
}

float AMyActor::CalculationDistance(FVector2D OriginPosition, FVector2D MovedPosition)
{
	return FMath::Sqrt(FMath::Pow(MovedPosition.X - OriginPosition.X, 2) + FMath::Pow(MovedPosition.Y - OriginPosition.Y, 2));
}

bool AMyActor::CreateEvent()
{
	return FMath::RandBool();
}