// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Tower.h"
#include "Tank.h"
#include "BasePawn.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));


	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);


	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UHealthComponent::DamageTaken(AActor* DamagedActor, float DamageValue, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser) {

	ABasePawn* ThisPawn = Cast<ABasePawn>(GetOwner());

	if (DamageValue <= 0.f) return;

	CurrentHealth -= DamageValue;

	if (CurrentHealth <= 50 && ToonTanksGameMode) {
		ThisPawn->EmitSmoke();

	} else if (CurrentHealth > DangerHealth && ToonTanksGameMode) {
		ThisPawn->RemoveSmoke();
	}

	if (CurrentHealth <= 0 && ToonTanksGameMode) {

		ToonTanksGameMode->ActorDied(DamagedActor);
	}

}

float UHealthComponent::GetCurrentHealth() const {

	return CurrentHealth;

}

float UHealthComponent::GetMaxHealth() const {

	return MaxHealth;

}

void UHealthComponent::SetHealth(float Value) {

	CurrentHealth = Value;
}