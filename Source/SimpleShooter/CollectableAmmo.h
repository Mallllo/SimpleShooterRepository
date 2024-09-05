// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "CollectableAmmo.generated.h"

/**
 *
 */
UCLASS()
class SIMPLESHOOTER_API ACollectableAmmo : public ACollectable
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	// 탄약이 가득차지 않았으면 적과 아군 상관없이 모두 충전, 충전시 일정시간 비활성화
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent *OverlappedComponent,
				   AActor *OtherActor,
				   UPrimitiveComponent *OtherComp,
				   int32 OtherBodyIndex,
				   bool bFromSweep,
				   const FHitResult &SweepResult);

private:
	// 비활성화 되는 시간
	float ReactivateDuration = 3.0f;
	// 탄약 충전 양
	UPROPERTY(EditAnywhere)
	int ChargeAmount = 50;
};
