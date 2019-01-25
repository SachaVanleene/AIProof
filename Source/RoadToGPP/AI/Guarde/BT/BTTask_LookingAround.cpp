// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_LookingAround.h"
#include "Animation/AnimInstance.h"
#include "Anim/MyAnimInstance.h"
#include "AIController.h"

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
	FVector test = OwnerComp.GetOwner()->GetTransform().GetLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("VECTOR %.2f, %.2f, %.2f"), test.X, test.Y, test.Z));
	m_meshComp = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<USkeletalMeshComponent>();
	m_animInstance = Cast<UMyAnimInstance>(m_meshComp->GetAnimInstance());
	if (m_animInstance)
	{
		m_isAnimTriggered = true;
		m_animInstance->isLookingAround = true;
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}



