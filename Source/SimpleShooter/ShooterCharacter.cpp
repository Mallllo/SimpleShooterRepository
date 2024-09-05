// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "KillEmAllGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController *PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	// Spawn every Guns
	for (TSubclassOf<AGun> GunIterator : GunClasses)
	{
		AGun *SpawnedGun = GetWorld()->SpawnActor<AGun>(GunIterator);
		SpawnedGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		SpawnedGun->SetOwner(this);
		Guns.Emplace(SpawnedGun);
	}
	// Hide spawned guns
	for (AGun *GunIterator : Guns)
	{
		GunIterator->Activate(false);
	}
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	// unhide current gun
	if (Guns.IsValidIndex(CurrentGunIndex))
	{
		CurrentGun = Guns[CurrentGunIndex];
		CurrentGun->Activate(true);
	}
	CurrentHealth = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AShooterCharacter::ShooterCharacterJump);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &AShooterCharacter::ShooterCharacterReload);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterCharacter::ShooterCharacterMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterCharacter::ShooterCharacterLook);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AShooterCharacter::ShooterCharacterShoot);
		EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Triggered, this, &AShooterCharacter::ShooterCharacterSwitchWeapon);
	}
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float FinalDamage = FMath::Min(CurrentHealth, DamageToApply);
	CurrentHealth -= FinalDamage;
	if (IsDead())
	{
		AKillEmAllGameModeBase *GameMode = GetWorld()->GetAuthGameMode<AKillEmAllGameModeBase>();
		if (GameMode)
		{
			GameMode->PawnKilled(this);
		}
		// PawnKilled를 먼저 실행하고 DetachFromControllerPendingDestroy를 실행
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return FinalDamage;
}

bool AShooterCharacter::IsDead() const
{
	return CurrentHealth <= 0;
}

float AShooterCharacter::GetPercentHealth() const
{
	return CurrentHealth / MaxHealth;
}

int AShooterCharacter::GetCurrentGunAmmo() const
{
	return CurrentGun->GetCurrentAmmo();
}

int AShooterCharacter::GetCurrentGunMagazine() const
{
	return CurrentGun->GetCurrentMagazine();
}

AGun *AShooterCharacter::GetCurrentGun() const
{
	return CurrentGun;
}

/** Called for movement input */
void AShooterCharacter::ShooterCharacterMove(const FInputActionValue &Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	if (Controller)
	{
		FRotator CharacterYaw = FRotator(0, Controller->GetControlRotation().Yaw, 0);
		FVector CharacterForward = FRotationMatrix(CharacterYaw).GetUnitAxis(EAxis::X);
		FVector CharacterRight = FRotationMatrix(CharacterYaw).GetUnitAxis(EAxis::Y);

		AddMovementInput(CharacterForward, Input.Y);
		AddMovementInput(CharacterRight, Input.X);
	}
}

/** Called for looking input */
void AShooterCharacter::ShooterCharacterLook(const FInputActionValue &Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerPitchInput(Input.Y);
		AddControllerYawInput(Input.X);
	}
}

void AShooterCharacter::ShooterCharacterJump(const FInputActionValue &Value)
{
	if (Controller)
	{
		Jump();
	}
}

void AShooterCharacter::ShooterCharacterReload(const FInputActionValue &Value)
{
	if (CurrentGun)
	{
		CurrentGun->Reload();
	}
}

void AShooterCharacter::ShooterCharacterShoot()
{
	if (CurrentGun)
	{
		CurrentGun->TriggerPulled();
	}
}

void AShooterCharacter::ShooterCharacterSwitchWeapon(const FInputActionValue &Value)
{
	CurrentGun->Activate(false);
	float Input = Value.Get<float>();
	if (Guns.Num() > 0)
	{
		if (Input < 0)
		{
			// Make Index Iteration ex) 0,1,2,3,4,0,1,2,3,4,.....
			CurrentGunIndex--;
			if (CurrentGunIndex < 0)
			{
				CurrentGunIndex += Guns.Num();
			}
			CurrentGunIndex %= Guns.Num();
			CurrentGun = Guns[CurrentGunIndex];
			CurrentGun->Activate(true);
		}
		else
		{
			CurrentGunIndex++;
			CurrentGunIndex %= Guns.Num();
			CurrentGun = Guns[CurrentGunIndex];
			CurrentGun->Activate(true);
		}
	}
}
