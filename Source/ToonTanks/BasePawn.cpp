// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/WorldPSCPool.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	DamagedEmitter = CreateDefaultSubobject<USceneComponent>(TEXT("Smoke Emit Point"));
	DamagedEmitter->SetupAttachment(TurretMesh);

	

}

void ABasePawn::HandleDestruction(){
	


	//TODO: Visual/Sound effects
	if (DeathSound){


		//Finds the distance between the Tank and the Actor and gets the loudness factor of the Volume used for the Death sound
		FVector TankPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		FVector CurrentPosition = GetActorLocation();
		float Distance = FVector::Dist(CurrentPosition, TankPosition);
		float VolumeValue = NormalizeDist(Distance, MaxDist);

		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), VolumeValue);
	}
	
	if (DeathParticles) {
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation(), true);
	}

	if (DeathCameraShakeClass) {

		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}



	
}

void ABasePawn::RotateTurret(FVector LookAtTarget) 
{

	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = 	FRotator(0.f, ToTarget.Rotation().Yaw, 0.0f);
	
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(TurretMesh->GetComponentRotation(), 
		LookAtRotation, 
		UGameplayStatics::GetWorldDeltaSeconds(this), 
		10.0f)
		);



}

void ABasePawn::Fire()
{

	FVector ProjectileLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileRotation = ProjectileSpawnPoint->GetComponentRotation();


	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileLocation, ProjectileRotation);
	Projectile->SetOwner(this);


}

void ABasePawn::EmitSmoke() {

	if (DamagedParticles != nullptr) {
			EmitterComponent = UGameplayStatics::SpawnEmitterAttached(
				DamagedParticles, 
				DamagedEmitter,
				DamagedEmitter->GetFName(),
				FVector(-40.f, 0.f, 40.f), 
				FRotator(0.f, 0.f, 0.f),
				EAttachLocation::SnapToTarget,
				false,
				EPSCPoolMethod::None,
				true);
	}

	
}

void ABasePawn::RemoveSmoke() {

	if (EmitterComponent) {
		EmitterComponent->Deactivate();

	}

	
}

float ABasePawn::NormalizeDist(float currentDist, float MaxDistance) {

	float TotalDist = currentDist/MaxDist;

	if (TotalDist > 1) {

		return 0;
	}

	TotalDist = 1 -	TotalDist;
	return TotalDist;

}