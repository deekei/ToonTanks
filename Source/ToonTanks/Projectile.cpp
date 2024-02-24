// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	RootComponent = BulletMesh;

	BulletComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Bullet Comp"));



	BulletComp->InitialSpeed = InitialSpeed;
	BulletComp->MaxSpeed = MaxSpeed;
	
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	BulletMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);


	if (LaunchSound) {
		float PitchRange = UKismetMathLibrary::RandomFloatInRange(0.8f, 1.2f);
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), 1.0, PitchRange);
	}

	
}



// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult& Hit){

	//Using auto allows us to be flexible on what class type the owner of the Projectile class is
	AActor* MyOwner = GetOwner();

	if (!MyOwner) {

		Destroy();
		return;
	}

	//Initializes the type of the controller of the projectile's owner
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != Owner)
	{
		if (HitSound) {

			float PitchRange = UKismetMathLibrary::RandomFloatInRange(0.3f, 0.6f);
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(),0.5f,PitchRange);
		}


		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);

		if (HitParticles) {
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation(), true);
		}

		if (HitCameraShakeClass) {
			
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);

		}



	}

	Destroy();

}
