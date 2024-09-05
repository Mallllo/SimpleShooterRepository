// Fill out your copyright notice in the Description page of Project Settings.

#include "Launcher.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

void ALauncher::BeginPlay()
{
    Super::BeginPlay();
}

void ALauncher::SpawnBullet()
{
    FVector ViewLocation;
    FRotator ViewRotation;
    GetOwnerController()->GetPlayerViewPoint(ViewLocation, ViewRotation);
    FVector BulletSpawnPoint = ViewLocation + ((ViewRotation.Vector()) * BulletSpawnOffset);
    FActorSpawnParameters ActorSpawnParameter;
    ActorSpawnParameter.Owner = this;
    if (GetOwner())
    {
        ActorSpawnParameter.Instigator = Cast<APawn>(GetOwner());
    }
    AProjectile *SpawnedBullet = GetWorld()->SpawnActor<AProjectile>(LauncherProjectileClass, BulletSpawnPoint, ViewRotation, ActorSpawnParameter);
}

void ALauncher::TriggerPulled()
{
    if (!bCanShoot || bIsReloading)
    {
        return;
    }
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
    SpawnBullet();
    UGameplayStatics::SpawnSoundAttached(ShotSound, Mesh, TEXT("MuzzleFlashSocket"));
    UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleDustForLauncher, Mesh, TEXT("MuzzleFlashSocket"), FVector(ForceInit), FRotator::ZeroRotator, EAttachLocation::Type::KeepWorldPosition, true);
    CurrentMagazine--;
    CurrentAmmo--;
    DisableShootForSeconds(ShotDelay);
    if (CurrentMagazine <= 0)
    {
        Reload();
    }
}

void ALauncher::SpawnImpactEffectAtLocationWithRotation(FVector Location, FRotator Rotation)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffectForLauncher, Location);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Location);
}

void ALauncher::RadialDamageAtLocation(FVector Location)
{
    TArray<AActor *> ActualIgnoreActors;
    if (!CanDamageMySelf)
    {
        ActualIgnoreActors.Append(IgnoreActors);
        ActualIgnoreActors.Emplace(GetOwner());
    }
    else
    {
        ActualIgnoreActors.Append(IgnoreActors);
    }
    UGameplayStatics::ApplyRadialDamageWithFalloff(
        GetWorld(),
        DamageAmount,
        MinimumDamage,
        Location,
        DamageInnerRadius,
        DamageOuterRadius,
        DamageFalloff,
        UDamageType::StaticClass(),
        ActualIgnoreActors,
        this,
        GetOwnerController());
}
