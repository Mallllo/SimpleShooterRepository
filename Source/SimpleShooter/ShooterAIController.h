// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	// KillEmAllGameMode에서 적이 모두 죽었는지 판단할 때 사용
	bool IsDead() const;
private:
	//Behavior Tree
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
};
