// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoPowerUp.h"
#include "PowerUp.h"
#include "Tank.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

AAmmoPowerUp::AAmmoPowerUp() 
{


}

void AAmmoPowerUp::ActivatePowerUp() {

    
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	


    float MaxAmmoVlaue = Tank->GetMaxAmmoValue();
    float CurrentAmmoValue = Tank->GetAmmoValue();

    if (CurrentAmmoValue < MaxAmmoVlaue) {

	    Tank->RecoverAmmo(AmmoValue);
        Super::ActivatePowerUp();

    }

}