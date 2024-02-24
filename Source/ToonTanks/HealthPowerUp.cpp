// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPowerUp.h"
#include "HealthComponent.h"
#include "PowerUp.h"
#include "Tank.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

AHealthPowerUp::AHealthPowerUp() {


}

void AHealthPowerUp::ActivatePowerUp() {

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

    auto TankHealthComp = Tank->GetComponentByClass(UHealthComponent::StaticClass());

    MaxHealth = Cast<UHealthComponent>(TankHealthComp)->GetMaxHealth();

    float CurrentHealth = Cast<UHealthComponent>(TankHealthComp)->GetCurrentHealth();

    if (CurrentHealth < MaxHealth) {

            if (CurrentHealth >= DangerHealth) {

                Tank->RemoveSmoke();
            }

        Cast<UHealthComponent>(TankHealthComp)->SetHealth(MaxHealth);
        Super::ActivatePowerUp();
    }



}