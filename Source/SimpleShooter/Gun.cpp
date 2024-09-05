// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "Components/AudioComponent.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::TriggerPulled()
{
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MaxAmmo;
	CurrentMagazine = MagazineCapacity;
}

AController *AGun::GetOwnerController() const
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;
	return OwnerPawn->GetController();
}

void AGun::EnableShoot(bool InCanShoot)
{
	bCanShoot = InCanShoot;
}

void AGun::DisableShootForSeconds(float Delay)
{
	FTimerHandle ShotDelayTimerHandle;
	FTimerDelegate ShotDelayTimerDelegate = FTimerDelegate::CreateUObject(this, &AGun::EnableShoot, true);
	GetWorldTimerManager().SetTimer(ShotDelayTimerHandle, ShotDelayTimerDelegate, Delay, false);
	EnableShoot(false);
}

void AGun::SetIsReloading(bool IsReloading)
{
	bIsReloading = IsReloading;
}

bool AGun::GetIsReloading() const
{
	return bIsReloading;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::Reload()
{
	if (bIsReloading)
	{
		return;
	}
	if (CurrentMagazine == MagazineCapacity)
	{
		return;
	}
	if (CurrentAmmo == 0)
	{
		return;
	}
	// 재장전 상태 업데이트
	FTimerHandle ReloadTimerHandle;
	FTimerDelegate ReloadTimerDelegate = FTimerDelegate::CreateUObject(this, &AGun::SetIsReloading, false);
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, ReloadTimerDelegate, ReloadDelay, false);
	SetIsReloading(true);
	SpawnedReloadingSound = UGameplayStatics::SpawnSoundAttached(ReloadSound, Mesh);
	// 재장전 시간 지난 후에 탄약 충전 - 재장전 취소 시 충전 안됨
	GetWorldTimerManager().SetTimer(AddMagazineTimerHandle, this, &AGun::AddMagazine, ReloadDelay);
}

void AGun::AddAmmo(int AmmoAmount)
{
	CurrentAmmo += AmmoAmount;
	if (CurrentAmmo > MaxAmmo)
	{
		CurrentAmmo = MaxAmmo;
	}
}

void AGun::AddMagazine()
{
	int ReloadAmount = MagazineCapacity - CurrentMagazine;
	int ActualReloadAmount = FMath::Min(ReloadAmount, CurrentAmmo);
	CurrentMagazine += ActualReloadAmount;
}

int AGun::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

int AGun::GetCurrentMagazine() const
{
	return CurrentMagazine;
}

float AGun::GetReloadAnimationRate() const
{
    return ReloadAnimationRate;
}

bool AGun::IsFullAmmo() const
{
	return CurrentAmmo == MaxAmmo;
}

void AGun::Activate(bool State)
{
	SetActorHiddenInGame(!State);
	if (!State)
	{
		CancelReload();
	}
}

void AGun::CancelReload()
{
	GetWorldTimerManager().ClearTimer(AddMagazineTimerHandle);
	if (SpawnedReloadingSound)
	{
		SpawnedReloadingSound->Stop();
	}
	SetIsReloading(false);
}
