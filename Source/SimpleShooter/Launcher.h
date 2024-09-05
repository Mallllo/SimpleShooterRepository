// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Launcher.generated.h"

/**
 * 
 */
class AProjectile;

UCLASS()
class SIMPLESHOOTER_API ALauncher : public AGun
{
	GENERATED_BODY()
public:
	virtual void TriggerPulled() override;

	// 이펙트와 데미지 적용 함수는 Projectile에서 호출 가능해야함
	void SpawnImpactEffectAtLocationWithRotation(FVector Location, FRotator Rotation);
	void RadialDamageAtLocation(FVector Location);
protected:
	virtual void BeginPlay() override;
private:
	//스폰할 투사체 관련 멤버
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> LauncherProjectileClass;
	UPROPERTY(EditAnywhere)
	float BulletSpawnOffset = 100.0f;
	void SpawnBullet();

	// 데미지 적용 관련 멤버
	UPROPERTY(EditAnywhere)
	float DamageFalloff = 1.0f;
	UPROPERTY(EditAnywhere)
	float DamageInnerRadius = 50.0f;
	UPROPERTY(EditAnywhere)
	float DamageOuterRadius = 100.0f;
	UPROPERTY(EditAnywhere)
	float MinimumDamage = 30.0f;

	// 데미지를 적용하지 않을 액터 목록(충돌은 일어남)
	UPROPERTY(EditAnywhere)
	TArray<AActor*> IgnoreActors;
	// true이면 자기 자신에게 데미지 적용됨(RadialDamageAtLocation함수에 구현)
	UPROPERTY(EditAnywhere)
	bool CanDamageMySelf = false;

	// 부모 클래스와 다르게 Niagara System을 사용하기 위해 별도로 선언
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* ImpactEffectForLauncher;
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* MuzzleDustForLauncher;

};
