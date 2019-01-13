// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Patroil.generated.h"

UCLASS()
class ROADTOGPP_API UBTTask_Patroil : public UBTTask_BlackboardBase
{
	UBTTask_Patroil() : m_currentPatroilTarget(nullptr), isMovingToLocation(false) {};

	GENERATED_BODY()


		UPROPERTY(EditAnywhere, Category = "Patroil")
		TArray<FVector> m_PatroilPos;


	FVector * m_currentPatroilTarget;
	bool isMovingToLocation;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	bool ChoseNextPos();

	bool HasReachedTargetPos(UBehaviorTreeComponent& OwnerComp);
};
