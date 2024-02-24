// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h" 

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	virtual void Fire();

	void HandleDestruction();

	void EmitSmoke();

	
	void RemoveSmoke();
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

protected:

	void RotateTurret(FVector LookAtTarget);



private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Components")
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Components")
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Components")
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Components")
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Components")
	USceneComponent* DamagedEmitter;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Components")
	UParticleSystemComponent* EmitterComponent;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Components")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Components")
	class UParticleSystem* DamagedParticles;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Combat")
	class USoundBase* DeathSound;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	float MaxDist = 1000.f;

	float NormalizeDist(float currentDist, float MaxDist);


};
