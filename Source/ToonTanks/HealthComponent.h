// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	float DangerHealth = 50.f;;

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float DamageValue, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);
	
	float CurrentHealth = 0.f; 

	class AToonTanksGameMode* ToonTanksGameMode;

	class ATank* Tank;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	void SetHealth(float Value);

		
};
