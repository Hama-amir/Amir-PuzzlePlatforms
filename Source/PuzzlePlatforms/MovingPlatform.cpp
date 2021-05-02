// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform() 
{
    PrimaryActorTick.bCanEverTick = true;

    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() 
{
    Super::BeginPlay();
    
    if(HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    } 
    
    InitialLocation = GetActorLocation();
    CurrentLocation = InitialLocation;
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::AddActiveTrigger() 
{
    ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger() 
{
    if(ActiveTriggers > 0)
    {
       ActiveTriggers--; 
    }
}

void AMovingPlatform::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if(ActiveTriggers > 0)
    {
        if(HasAuthority())
        {
            float JourneyLength = (GlobalTargetLocation - InitialLocation).Size();
            float JourneyTravelled = (CurrentLocation - InitialLocation).Size();

            if(JourneyTravelled >= JourneyLength) // if passed travel length, go back
            {
                GlobalTargetLocation = InitialLocation;
                InitialLocation = CurrentLocation;
            }
                
            FVector MovementDirection = (GlobalTargetLocation - InitialLocation).GetSafeNormal();
            CurrentLocation += Speed * DeltaTime * MovementDirection;
            SetActorLocation(CurrentLocation);
        }
    }
}

