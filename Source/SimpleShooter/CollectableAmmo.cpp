// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableAmmo.h"
#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"

void ACollectableAmmo::BeginPlay()
{
    Super::BeginPlay();
    CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &ACollectableAmmo::OnOverlap);
}

void ACollectableAmmo::OnOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    AShooterCharacter* OverlappedCharacter = Cast<AShooterCharacter>(OtherComp->GetOwner());
    if(OverlappedCharacter)
    {
        AGun* CharacterGun = OverlappedCharacter->GetCurrentGun();
        if (CharacterGun && !CharacterGun->IsFullAmmo())
        {
            CharacterGun->AddAmmo(ChargeAmount);
            UGameplayStatics::PlaySound2D(GetWorld(), PickupSound);
            SetDisabled(true);

            FTimerHandle ReactivateTimerHandle;
            FTimerDelegate ReactivateTimerDelegate = FTimerDelegate::CreateUObject(this,&ACollectable::SetDisabled, false);
            // FTimerDelegate ReactivateTimerDelegate;
            // ReactivateTimerDelegate.BindUFunction(this, FName("SetDisabled"), false);
            GetWorldTimerManager().SetTimer(ReactivateTimerHandle,ReactivateTimerDelegate,ReactivateDuration,false);
            
        }
    }
}
