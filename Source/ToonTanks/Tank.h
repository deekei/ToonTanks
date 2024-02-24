// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()


public:
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RecoverAmmo(float Value);

	UFUNCTION(BlueprintPure)
	float GetAmmoValue() const;

	UFUNCTION(BlueprintPure)
	float GetMaxAmmoValue() const;

	

	APlayerController* GetTankPlayerController() const {return TankPlayerController; }

	bool bAlive = true;

protected:

	virtual void BeginPlay() override;


	void Fire() override; 
	void Pause();


private:

	float Speed = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float CurrentSpeed = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float SetSpeed = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Acceleration = 0.01f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float TurnRate = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Ammo = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxAmmo = 5.0f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	void Move(float Value);
	void Turn (float Value);

	void Dash(float Value);

	bool bPaused = false;

	APlayerController* TankPlayerController;
	
};
