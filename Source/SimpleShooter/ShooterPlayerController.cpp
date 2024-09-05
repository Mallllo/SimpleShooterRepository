// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    if(bIsWinner)
    {
        UUserWidget *WinWidget = CreateWidget(this, WinWidgetClass);
        if (WinWidget)
        {
            WinWidget->AddToViewport();
            if(HUDWidget)
            {
                HUDWidget->RemoveFromParent();
            }
        }
    }
    else
    {
        UUserWidget *LoseWidget = CreateWidget(this, LoseWidgetClass);
        if (LoseWidget)
        {
            LoseWidget->AddToViewport();
            if(HUDWidget)
            {
                HUDWidget->RemoveFromParent();
            }
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

float AShooterPlayerController::GetRestartDelay() const
{
    return RestartDelay;
}

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    HUDWidget = CreateWidget(this, HUDWidgetClass);
    if(HUDWidget)
    {
        HUDWidget->AddToViewport();
    }
}
