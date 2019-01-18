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

	UBTTask_LookingAround() : m_animInstance(nullptr), m_meshComp(nullptr), m_isAnimTriggered(false) {};

	class USkeletalMeshComponent * m_meshComp;
	class UMyAnimInstance * m_animInstance;
	bool m_isAnimTriggered;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	inline EBTNodeResult::Type TriggerAnimation(UBehaviorTreeComponent& OwnerComp);
};
