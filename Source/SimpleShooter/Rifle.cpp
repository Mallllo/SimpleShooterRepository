// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"

void ARifle::TriggerPulled()
{
    if (!bCanShoot || bIsReloading)
    {
        return;
    }
    Super::TriggerPulled();
    if (CurrentMagazine <= 0)
	{
        if (CurrentAmmo > 0)
        {
            Reload();
            return;
        }
        else
        {
            UGameplayStatics::SpawnSoundAttached(EmptySound, Mesh, TEXT("MuzzleFlashSocket"));
			DisableShootForSeconds(ShotDelay);
            return;
        }
	}
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(ShotSound, Mesh, TEXT("MuzzleFlashSocket"));
	FHitResult Hit;
	FVector ShotDirection;
	if (GunShootTrace(Hit, ShotDirection))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, ShotDirection.Rotation(), true);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.ImpactPoint);
		AActor *HitActor = Hit.GetActor();
		if (HitActor)
		{
			FPointDamageEvent DamageEvent(DamageAmount, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(DamageAmount, DamageEvent, GetOwnerController(), this);
		}
	}
	CurrentMagazine--;
	CurrentAmmo--;
	DisableShootForSeconds(ShotDelay);
	if (CurrentMagazine <= 0)
    {
        Reload();
    }
}

bool ARifle::GunShootTrace(FHitResult &OutHit, FVector &OutShotDirection)
{
    FRotator ViewRotation;
	FVector ViewLocation;
	GetOwnerController()->GetPlayerViewPoint(ViewLocation, ViewRotation);
	FVector ViewDirection = ViewRotation.Vector();
	FVector BulletEnd = ViewLocation + ViewDirection * MaxRange;
	OutShotDirection = -ViewDirection;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(OutHit, ViewLocation, BulletEnd, ECC_GameTraceChannel1, Params);
}
