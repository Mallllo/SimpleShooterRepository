// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	//승리/패배 시 알맞는 위젯 띄워줌
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	//Widget BP를 위한 함수
	UFUNCTION(BlueprintPure)
	float GetRestartDelay() const;
private:
	//경기 종료 시 재시작
	FTimerHandle RestartTimer;
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.0f;
	//승리, 패배, HUD위젯
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* HUDWidget;
	
	protected:
	virtual void BeginPlay() override;
};
