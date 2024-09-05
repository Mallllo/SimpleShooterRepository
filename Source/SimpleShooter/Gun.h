// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"
UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	float DamageAmount = 10;

	// 탄약 관련 변수
	UPROPERTY(EditAnywhere)
	int MaxAmmo = 250;
	UPROPERTY(EditAnywhere)
	int MagazineCapacity = 50;
	int CurrentAmmo;
	int CurrentMagazine;

	// 메시, 파티클, 타격음
	UPROPERTY(VisibleAnywhere)
	USceneComponent *Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent *Mesh;
	UPROPERTY(EditAnywhere)
	UParticleSystem *MuzzleFlash;
	UPROPERTY(EditAnywhere)
	USoundBase *ShotSound;
	UPROPERTY(EditAnywhere)
	USoundBase *ImpactSound;
	UPROPERTY(EditAnywhere)
	USoundBase *EmptySound;
	UPROPERTY(EditAnywhere)
	USoundBase *ReloadSound;
	UPROPERTY(EditAnywhere)
	UParticleSystem *ImpactEffect;

	// 사격 시 플레이어 컨트롤러의 Viewpoint 가져올 때 사용
	AController *GetOwnerController() const;

	// 연사 시스템
	UPROPERTY(EditAnywhere)
	float ShotDelay = 0.1f;
	bool bCanShoot = true;
	UFUNCTION()
	void EnableShoot(bool InCanShoot);
	void DisableShootForSeconds(float Delay);

	// 재장전 시스템
	UPROPERTY(EditAnywhere)
	float ReloadDelay = 1.f;
	UPROPERTY(EditAnywhere)
	float ReloadAnimationRate = 1.0f;
	bool bIsReloading = false;
	void SetIsReloading(bool IsReloading);
	void CancelReload();
	// 탄약 충전 함수 별도로 만들어서 ClearTimer로 재장전 취소
	void AddMagazine();

private:
	// 재장전 취소 시 ClearTimer하기 위해 멤버로 저장
	FTimerHandle AddMagazineTimerHandle;
	// 재장전 취소 시 사운드 실행 중단 위해 멤버로 저장
	UAudioComponent* SpawnedReloadingSound;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Animation Blueprint를 위한 함수들
	UFUNCTION(BlueprintPure)
	float GetReloadAnimationRate() const;
	UFUNCTION(BlueprintPure)
	bool GetIsReloading() const;
	int GetCurrentAmmo() const;
	int GetCurrentMagazine() const;

	// Collectable Ammo 시스템에서 사용
	UFUNCTION(BlueprintCallable)
	void AddAmmo(int AmmoAmount);
	bool IsFullAmmo() const;

	// 무기 변경 메커니즘에서 활성화/비활성화를 위한 함수
	void Activate(bool State);

	// 사격 - ShooterCharacter에서 사용
	virtual void TriggerPulled();
	// 재장전 - ShooterCharacter에서 사용
	UFUNCTION(BlueprintCallable)
	void Reload();
};
