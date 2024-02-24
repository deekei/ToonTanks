// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "AmmoPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AAmmoPowerUp : public APowerUp
{
	GENERATED_BODY()

public:
	AAmmoPowerUp();

	void ActivatePowerUp() override;

private:
	class ATank* Tank;
};
