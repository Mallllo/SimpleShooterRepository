// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//자식 블루프린트 상속을 위해 Protected
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

private:
	//Input Action
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* ReloadAction;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* SwitchWeaponAction;

	//Imput Mapping Context
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* InputMappingContext;

	//Input Action에 Bind하기 위한 함수들
	void ShooterCharacterMove(const FInputActionValue& Value);
	void ShooterCharacterLook(const FInputActionValue& Value);
	void ShooterCharacterJump(const FInputActionValue& Value);
	void ShooterCharacterReload(const FInputActionValue& Value);
	void ShooterCharacterSwitchWeapon(const FInputActionValue& Value);

	//총기 전환 시스템을 위한 멤버들
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<class AGun>> GunClasses;
	TArray<AGun*> Guns;
	AGun* CurrentGun;
	int CurrentGunIndex = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	//BTTask에서 사용하기 위해 public으로 선언
	void ShooterCharacterShoot();
	
	//Animation Blueprint에서 사용할 함수들
	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	UFUNCTION(BlueprintPure)
	float GetPercentHealth() const;
	UFUNCTION(BlueprintPure)
	int GetCurrentGunAmmo() const;
	UFUNCTION(BlueprintPure)
	int GetCurrentGunMagazine() const;
	UFUNCTION(BlueprintPure)
	AGun* GetCurrentGun() const;
};
