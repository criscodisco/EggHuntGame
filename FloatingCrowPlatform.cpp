// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingCrowPlatform.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"

// Sets default values
AFloatingCrowPlatform::AFloatingCrowPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	//Mesh->SetupAttachment(CollisionCapsule);
	Mesh->SetupAttachment(GetRootComponent());
	StartPoint = FVector(0.f);
	EndPoint = FVector(0.f);
	EndPoint2 = FVector(0.f);

	AddToVectorOffset = FVector(0.f);
	AddToVectorOffsetAgain = FVector(0.f);

	bInterping = false;

	InterpSpeed = 0.25f;
	InterpTime =  .5f;
}

// Called when the game starts or when spawned
void AFloatingCrowPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartPoint = GetActorLocation();

	EndPoint = GetActorLocation() + AddToVectorOffset;

	EndPoint2 = EndPoint + AddToVectorOffsetAgain;

	bInterping = false;

	Distance = (EndPoint - StartPoint).Size();

	Distance2 = (EndPoint2 - EndPoint).Size();
}

// Called every frame
void AFloatingCrowPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInterping)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector Interp = FMath::VInterpTo(CurrentLocation, EndPoint, DeltaTime, InterpSpeed);
		SetActorLocation(Interp);

		GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingCrowPlatform::ToggleInterping, InterpTime);
		
		float DistanceTraveled = (GetActorLocation() - StartPoint).Size();
		if (Distance - DistanceTraveled <= 500.f)
		{
			CurrentLocation = GetActorLocation();
			EndPoint2 = CurrentLocation + AddToVectorOffsetAgain;
			FVector Interp2 = FMath::VInterpTo(CurrentLocation, EndPoint2, DeltaTime, InterpSpeed);
			SetActorLocation(Interp2);

			float DistanceTraveledAgain = (GetActorLocation() - EndPoint).Size();
			if (Distance2 - DistanceTraveledAgain <= 500.f)
			{
			}
		}
		
	}
	
}

void AFloatingCrowPlatform::ToggleInterping()
{
	bInterping = !bInterping;
}

void AFloatingCrowPlatform::SwapVectors(FVector& VecOne, FVector& VecTwo)
{
	FVector Temp = VecOne;
	VecOne = VecTwo;
	VecTwo = Temp;
}