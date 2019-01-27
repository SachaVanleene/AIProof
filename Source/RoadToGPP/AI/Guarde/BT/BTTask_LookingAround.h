// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookingAround.generated.h"

/**
 * 
 */

UCLASS()
class ROADTOGPP_API UBTTask_LookingAround : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_LookingAround() : 
		m_animInstance(nullptr),
		m_isAnimTriggered(false),
		m_stateMachineIndex(0),
		m_animIndex(0),
		m_seuilAnimFinished(0.02f)
	{
		Super::bNotifyTick = 1;
	};

	class UMyAnimInstance * m_animInstance;
	float m_seuilAnimFinished;
	int32 m_stateMachineIndex;
	int32 m_animIndex;
	bool m_isAnimTriggered;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds) override;

	inline EBTNodeResult::Type TriggerAnimation(UBehaviorTreeComponent& OwnerComp);
};
