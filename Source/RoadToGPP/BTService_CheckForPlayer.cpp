// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_CheckForPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "GuardeCharacter.h"
#include "GuardAI.h"



UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
	bCreateNodeInstance = true;
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AGuardAI * guardAI = Cast<AGuardAI>(OwnerComp.GetAIOwner());

	if (guardAI)
	{
		APawn * enemy = GetWorld()->GetFirstPlayerController()->GetPawn();

		if (enemy)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(guardAI->m_EnnemyKeyID, enemy);
		}
	}
}
