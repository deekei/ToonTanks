// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "Tank.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	BaseMesh->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::BeginOverlap);

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	

}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void APowerUp::BeginOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {

	//if the Other Actors class is a Projectile Class, it ignores the overlap
	if(OtherActor->GetClass()->IsChildOf(AProjectile::StaticClass())) {

		
	} else {

		if (Tank) {

			ActivatePowerUp();

			}

	}

}


void APowerUp::ActivatePowerUp() {

	this->Destroy();
}
