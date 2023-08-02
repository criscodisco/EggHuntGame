// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "BossBearEnemy.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API ABossBearEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ABossBearEnemy();

	bool bHasValidTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat Collision")
	class UBoxComponent* LeftArmCombatCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat Collision")
	class UBoxComponent* RightArmCombatCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat Collision")
	class UBoxComponent* VulnerabilityCollision;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void RightArmCombatCollisionOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void RightArmCombatCollisionOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void LeftArmCombatCollisionOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void LeftArmCombatCollisionOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void VulnerabilityCollisionOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void VulnerabilityCollisionOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
	void AttackLeftArm();
	UFUNCTION(BlueprintCallable)
	void AttackRightArm();
	UFUNCTION(BlueprintCallable)
	void AttackLeftArmEnd();
	UFUNCTION(BlueprintCallable)
	void AttackRightArmEnd();
	UFUNCTION(BlueprintCallable)
	void ActivateLeftArmCollision();
	UFUNCTION(BlueprintCallable)
	void ActivateRightArmCollision();
	UFUNCTION(BlueprintCallable)
	void DeactivateLeftArmCollision();
	UFUNCTION(BlueprintCallable)
	void DeactivateRightArmCollision();

};
