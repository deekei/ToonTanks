// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Combat")
	class UStaticMeshComponent* BulletMesh;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	class UProjectileMovementComponent* BulletComp;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	float InitialSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	float MaxSpeed = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	float Damage = 50.f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Combat")
	class UParticleSystem* HitParticles;	


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Combat")
	class UParticleSystemComponent* TrailParticles;	


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"), Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
};

