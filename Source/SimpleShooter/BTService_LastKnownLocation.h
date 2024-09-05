// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_LastKnownLocation.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTService_LastKnownLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_LastKnownLocation();
protected:
	// PlayerPawn 0의 위치를 Key(Vector)에 Set
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
