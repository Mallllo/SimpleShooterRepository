// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

UCLASS()
class SIMPLESHOOTER_API ACollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();
	UFUNCTION()
	// bIsDisabled가 true면 아이템 비활성화
	void SetDisabled(bool bIsDisabled);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleCollider;
	UPROPERTY(EditAnywhere)
	class USoundBase* PickupSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	

};
