// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBearEnemy.h"
#include "Components/BoxComponent.h"
#include "Main.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"
#include "MainPlayerController.h"
#include "AIController.h"


// Sets default values
ABossBearEnemy::ABossBearEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	RightArmCombatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightArmCombatCollision"));
	RightArmCombatCollision->SetupAttachment(GetMesh(), FName("rightArmrootSocket"));

	LeftArmCombatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftArmCombatCollision"));
	LeftArmCombatCollision->SetupAttachment(GetMesh(), FName("leftArmrootSocket"));

	VulnerabilityCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("VulnerabilityCollision"));
	VulnerabilityCollision->SetupAttachment(GetMesh(), FName("vulnerabilitySocket"));

	EnemyMovementStatus = EEnemyMovementStatus::EMS_Idle;


}

// Called when the game starts or when spawned
void ABossBearEnemy::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AAIController>(GetController());

	

	RightArmCombatCollision->OnComponentBeginOverlap.AddDynamic(this, &ABossBearEnemy::RightArmCombatCollisionOnOverlapBegin);
	RightArmCombatCollision->OnComponentEndOverlap.AddDynamic(this, &ABossBearEnemy::RightArmCombatCollisionOnOverlapEnd);

	RightArmCombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightArmCombatCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightArmCombatCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightArmCombatCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	LeftArmCombatCollision->OnComponentBeginOverlap.AddDynamic(this, &ABossBearEnemy::LeftArmCombatCollisionOnOverlapBegin);
	LeftArmCombatCollision->OnComponentEndOverlap.AddDynamic(this, &ABossBearEnemy::LeftArmCombatCollisionOnOverlapEnd);

	LeftArmCombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftArmCombatCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftArmCombatCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftArmCombatCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	VulnerabilityCollision->OnComponentBeginOverlap.AddDynamic(this, &ABossBearEnemy::VulnerabilityCollisionOnOverlapBegin);
	VulnerabilityCollision->OnComponentEndOverlap.AddDynamic(this, &ABossBearEnemy::VulnerabilityCollisionOnOverlapEnd);


	// Come back and adjust these collision settings to meet Boss requirements
	VulnerabilityCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	VulnerabilityCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	VulnerabilityCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	VulnerabilityCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called every frame
void ABossBearEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ABossBearEnemy::RightArmCombatCollisionOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMain* Main = Cast<AMain>(OtherActor);
		if (Main)
		{
			if (Main->HitParticles)
			{
				const USkeletalMeshSocket* RightArmSocket = GetMesh()->GetSocketByName("rightArmrootSocket");
				if (RightArmSocket)
				{
					FVector SocketLocation = RightArmSocket->GetSocketLocation(GetMesh());
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Main->HitParticles, SocketLocation, FRotator(0.f), false);
				}
			}
			if (Main->HitSound)
			{
				UGameplayStatics::PlaySound2D(this, Main->HitSound);
			}
			if (Main->DamageTypeClass)
			{
				UGameplayStatics::ApplyDamage(Main, Damage, AIController, this, DamageTypeClass);
			}
		}
	}
}


void ABossBearEnemy::RightArmCombatCollisionOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}




void ABossBearEnemy::LeftArmCombatCollisionOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMain* Main = Cast<AMain>(OtherActor);
		if (Main)
		{
			if (Main->HitParticles)
			{
				const USkeletalMeshSocket* LeftArmSocket = GetMesh()->GetSocketByName("leftArmrootSocket");
				if (LeftArmSocket)
				{
					FVector SocketLocation = LeftArmSocket->GetSocketLocation(GetMesh());
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Main->HitParticles, SocketLocation, FRotator(0.f), false);
				}
			}
			if (Main->HitSound)
			{
				UGameplayStatics::PlaySound2D(this, Main->HitSound);
			}
			if (Main->DamageTypeClass)
			{
				UGameplayStatics::ApplyDamage(Main, Damage, AIController, this, DamageTypeClass);
			}
		}
	}
}


void ABossBearEnemy::LeftArmCombatCollisionOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


void ABossBearEnemy::VulnerabilityCollisionOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMain* Main = Cast<AMain>(OtherActor);
		if (Main)
		{
			if (Main->HitParticles)
			{
				const USkeletalMeshSocket* VulnerabilitySocket = GetMesh()->GetSocketByName("vulnerabilitytSocket");
				if (VulnerabilitySocket)
				{
					FVector SocketLocation = VulnerabilitySocket->GetSocketLocation(GetMesh());
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Main->HitParticles, SocketLocation, FRotator(0.f), false);
				}
			}
			if (Main->HitSound)
			{
				UGameplayStatics::PlaySound2D(this, Main->HitSound);
			}
			if (Main->DamageTypeClass)
			{
				UGameplayStatics::ApplyDamage(Main, Damage, AIController, this, DamageTypeClass);
			}
		}
	}
}


void ABossBearEnemy::VulnerabilityCollisionOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}



void ABossBearEnemy::AttackLeftArm()
{
	if (Alive() && bHasValidTarget)
	{
		if (AIController)
		{
			AIController->StopMovement();
			SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Attacking);
		}
		if (!bAttacking)
		{
			bAttacking = true;
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				AnimInstance->Montage_Play(CombatMontage, 1.35f);
				AnimInstance->Montage_JumpToSection(FName("Attack_L_Arm"), CombatMontage);
			}
		}
	}
}

void ABossBearEnemy::AttackLeftArmEnd()
{
	bAttacking = false;
	if (bOverlappingCombatSphere)
	{
		float AttackTime = FMath::FRandRange(AttackMinTime, AttackMaxTime);
		GetWorldTimerManager().SetTimer(AttackTimer, this, &ABossBearEnemy::AttackLeftArm, AttackTime);
	}
}




void ABossBearEnemy::AttackRightArm()
{
	if (Alive() && bHasValidTarget)
	{
		if (AIController)
		{
			AIController->StopMovement();
			SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Attacking);
		}
		if (!bAttacking)
		{
			bAttacking = true;
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				AnimInstance->Montage_Play(CombatMontage, 1.35f);
				AnimInstance->Montage_JumpToSection(FName("Attack_R_Arm"), CombatMontage);
			}
		}
	}
}

void ABossBearEnemy::AttackRightArmEnd()
{
	bAttacking = false;
	if (bOverlappingCombatSphere)
	{
		float AttackTime = FMath::FRandRange(AttackMinTime, AttackMaxTime);
		GetWorldTimerManager().SetTimer(AttackTimer, this, &ABossBearEnemy::AttackRightArm, AttackTime);
	}
}

void ABossBearEnemy::ActivateLeftArmCollision()
{
	LeftArmCombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	if (SwingSound)
	{
		UGameplayStatics::PlaySound2D(this, SwingSound);
	}
}


void ABossBearEnemy::DeactivateLeftArmCollision()
{
	LeftArmCombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABossBearEnemy::ActivateRightArmCollision()
{
	RightArmCombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	if (SwingSound)
	{
		UGameplayStatics::PlaySound2D(this, SwingSound);
	}
}


void ABossBearEnemy::DeactivateRightArmCollision()
{
	RightArmCombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

