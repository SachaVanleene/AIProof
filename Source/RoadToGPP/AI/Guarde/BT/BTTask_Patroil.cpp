// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Patroil.h"
#include "AIController.h"


const float SEUIL = 100;


bool UBTTask_Patroil::HasReachedTargetPos(UBehaviorTreeComponent& OwnerComp)
{
	/*FVector test = *m_currentPatroilTarget;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("VECTOR %.2f, %.2f, %.2f"), test.X, test.Y, test.Z));*/
	AAIController *  aiC = OwnerComp.GetAIOwner();
	auto h = FVector::Dist(*m_currentPatroilTarget, aiC->GetPawn()->GetActorLocation());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("DIST %.2f"), h)); 
	if (FVector::Dist(*m_currentPatroilTarget, aiC->GetPawn()->GetActorLocation()) <= SEUIL)
	{
		return true;
	}

	return false;
}

bool UBTTask_Patroil::ChoseNextPos()
{
	if (m_PatroilPos.Num() == 0)
	{
		return false;
	}

	if (!m_currentPatroilTarget)
	{
		m_currentPatroilTarget = &m_PatroilPos[0];
	}
	else
	{
		if (m_currentPatroilTarget == &m_PatroilPos.Top())
		{
			m_currentPatroilTarget = &m_PatroilPos[0];
		}
		else
		{
			m_currentPatroilTarget++;
		}
	}

	return true;
}

//TODO : 
// Rework on BT
// Check if in progress is needed
// Second version with steering and wall avoidance
EBTNodeResult::Type UBTTask_Patroil::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (isMovingToLocation)
	{
		if (HasReachedTargetPos(OwnerComp))
		{
			isMovingToLocation = false;
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::InProgress;
	}
	else
	{
		if (ChoseNextPos())
		{
			OwnerComp.GetAIOwner()->MoveToLocation(*m_currentPatroilTarget, 5.f, true, true, true, true);
			isMovingToLocation = true;
			return EBTNodeResult::InProgress;
		}
	}

	return EBTNodeResult::Failed;
}

void UBTTask_Patroil::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (isMovingToLocation)
	{
		if (HasReachedTargetPos(OwnerComp))
		{
			isMovingToLocation = false;
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}


