// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class WORK5_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

private:
	FVector2D ActorPosition;
	FVector2D StartPosition;
	int32 EventCount;
	int32 StepCount;
	int32 Step();
	void Move();
	float CalculationDistance(FVector2D OriginPosition, FVector2D MovedPosition);
	bool CreateEvent();
};