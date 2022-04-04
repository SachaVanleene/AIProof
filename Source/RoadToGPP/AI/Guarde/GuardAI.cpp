// Fill out your copyright notice in the Description page of Project Settings.

#include "GuardAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "GuardeCharacterFix.h"

AGuardAI::AGuardAI() : 
	m_Pawn(nullptr)
{
	m_BlackBoard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("m_BlackBoard"));
	m_BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("m_BehaviorComponent"));
}

void AGuardAI::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	m_Pawn = InPawn;

	AGuardeCharacterFix * gCHar = Cast<AGuardeCharacterFix>(InPawn);

	if (gCHar && gCHar->m_Behavior)
	{
		m_BlackBoard->InitializeBlackboard(*gCHar->m_Behavior->BlackboardAsset);

		m_EnnemyKeyID = m_BlackBoard->GetKeyID("m_Target");

		m_BehaviorComponent->StartTree(*gCHar->m_Behavior);
	}
}

