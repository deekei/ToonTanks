// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "HealthPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AHealthPowerUp : public APowerUp
{
	GENERATED_BODY()

public:
	AHealthPowerUp();

	void ActivatePowerUp() override;

	float MaxHealth;
	float DangerHealth = 50.f;;

private:

	class ATank* Tank;

	class UHealthComponent* HealthComponent;
	
};
