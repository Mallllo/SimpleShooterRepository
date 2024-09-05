// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ARifle : public AGun
{
	GENERATED_BODY()
public:
	virtual void TriggerPulled() override;

private:
	//사격 가능 거리
	UPROPERTY(EditAnywhere)
	float MaxRange = 5000;
	//라인 트레이스를 위한 별도 함수
	bool GunShootTrace(FHitResult &OutHit, FVector &OutShotDirection);
	
};
