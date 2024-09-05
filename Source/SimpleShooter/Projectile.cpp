// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Launcher.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	RootComponent = StaticMesh;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	OwnerLauncher = Cast<ALauncher>(GetOwner());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	AActor *HitActor = Hit.GetActor();
	if (HitActor && OwnerLauncher)
	{
		OwnerLauncher->SpawnImpactEffectAtLocationWithRotation(Hit.ImpactPoint, (-(Hit.ImpactNormal)).Rotation());
		OwnerLauncher->RadialDamageAtLocation(Hit.ImpactPoint);
	}
	Destroy();
}
