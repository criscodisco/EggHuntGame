// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingCrowPlatform.generated.h"

UCLASS()
class FIRSTPROJECT_API AFloatingCrowPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingCrowPlatform();

	/** Mesh for the platform */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Platform")
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Platform")
		class UBoxComponent* CollisionCapsule;

	UPROPERTY(VisibleAnywhere)
		FVector StartPoint;

	UPROPERTY(VisibleAnywhere, meta = (MakeEditWidget = "true"))
		FVector EndPoint;

	UPROPERTY(VisibleAnywhere, meta = (MakeEditWidget = "true"))
		FVector EndPoint2;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform")
		FVector AddToVectorOffset;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Platform")
		FVector AddToVectorOffsetAgain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
		float InterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
		float InterpTime;

	FTimerHandle InterpTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
		bool bInterping;

	float Distance;
	float Distance2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleInterping();

	void SwapVectors(FVector& VecOne, FVector& VecTwo);

};
