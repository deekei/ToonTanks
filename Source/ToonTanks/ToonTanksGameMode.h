// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay();

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void DuringGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:

	class ATank* Tank;
	class ATower* Tower;
	FString LevelName;

	UPROPERTY(EditAnywhere)
	float StartDelay = 3.0f;

	void HandleGameStart();

	class AToonTanksPlayerController* ToonTankPlayerController;

	int32 TargetTowers = 0;

	int32 GetTargetTowerCount();

};
