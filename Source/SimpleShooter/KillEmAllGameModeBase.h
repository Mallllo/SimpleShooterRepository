// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameModeBase : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
public:
	//ShooterCharacter 클래스에서 TakeDamage함수를 통해 사망시 호출 - 게임 종료조건 달성 시 EndGame함수 실행
	virtual void PawnKilled(APawn* PawnKilled) override;
	//모든 컨트롤러의 GameHasEnded를 실행
	void EndGame(bool IsPlayerWinner);
};
