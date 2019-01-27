// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_LookingAround.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimStateMachineTypes.h"
#include "Anim/MyAnimInstance.h"
#include "AIController.h"

//SHOULD USE EVENT SYSTEM TO REWORK

EBTNodeResult::Type UBTTask_LookingAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector test = OwnerComp.GetOwner()->GetTransform().GetLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("VECTOR %.2f, %.2f, %.2f"), test.X, test.Y, test.Z));
	if (m_isAnimTriggered)
	{
		return EBTNodeResult::InProgress;
	}
	return TriggerAnimation(OwnerComp);
}

inline EBTNodeResult::Type UBTTask_LookingAround::TriggerAnimation(UBehaviorTreeComponent& OwnerComp)
{
	m_animInstance = Cast<UMyAnimInstance>(OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance());
	const FBakedAnimationStateMachine * fsmInstance = m_animInstance->GetStateMachineInstanceDesc("NainFSM");
	m_animIndex = fsmInstance->FindStateIndex("looking_around");
	m_stateMachineIndex = m_animInstance->GetStateMachineIndex("NainFSM");
	if (m_animInstance)
	{
		m_isAnimTriggered = true;
		m_animInstance->isLookingAround = true;
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

//TODO : HORRRIBLE ANIM SHOULD TRIGGER EVENT WE RECEIVE OR WHAT EVER CAUSE DEPEND ON TICK RATE .........
void UBTTask_LookingAround::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	float time_remaining = m_animInstance->GetRelevantAnimTimeRemainingFraction(m_stateMachineIndex, m_animIndex);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("TIME %.2f"), time_remaining));
	if (time_remaining <= m_seuilAnimFinished)
	{
		m_isAnimTriggered = false;
		m_animInstance->isLookingAround = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	EBTNodeResult::InProgress;
}



