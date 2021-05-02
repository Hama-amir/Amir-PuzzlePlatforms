// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatfromTrigger.h"

#include "Components/BoxComponent.h"
#include "MovingPlatform.h"

// Sets default values
APlatfromTrigger::APlatfromTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Volume"));
	
	if(!ensure(TriggerVolume != nullptr)) return;
	
	RootComponent = TriggerVolume;
}

// Called when the game starts or when spawned
void APlatfromTrigger::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatfromTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatfromTrigger::OnOverlapEnd);
	}

}

// Called every frame
void APlatfromTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatfromTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	for(AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
		UE_LOG(LogTemp, Warning, TEXT("Activated Platform"));
	}
}

void APlatfromTrigger::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	for(AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
		UE_LOG(LogTemp, Warning, TEXT("Deactivated Platform"));
	}
}



