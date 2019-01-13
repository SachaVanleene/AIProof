// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_MoveToPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GuardAI.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "GuardeCharacter.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGuardAI * guardPC = Cast<AGuardAI>(OwnerComp.GetAIOwner());


	APawn * Ennemy = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(guardPC->m_EnnemyKeyID));

	if (Ennemy)
	{
		guardPC->MoveToActor(Ennemy, 5.f, true, true, true, 0, true);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	EBTNodeResult::Failed;
}

