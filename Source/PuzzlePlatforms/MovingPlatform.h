// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	virtual void BeginPlay() override;

	void AddActiveTrigger();

	void RemoveActiveTrigger();

protected:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	FVector CurrentLocation;
	
	UPROPERTY()
	FVector InitialLocation;
	
	UPROPERTY(EditAnywhere)
	float Speed = 25.f;
	
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	FVector GlobalTargetLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;
};
