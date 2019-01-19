// Fill out your copyright notice in the Description page of Project Settings.

#include "GuardAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "GuardeCharacter.h"

AGuardAI::AGuardAI()
{
	m_BlackBoard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("m_BlackBoard"));
	m_BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("m_BehaviorComponent"));
}

void AGuardAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AGuardeCharacter * gCHar = Cast<AGuardeCharacter>(InPawn);

	if (gCHar && gCHar->GuardBehavior)
	{
		m_BlackBoard->InitializeBlackboard(*gCHar->GuardBehavior->BlackboardAsset);

		m_EnnemyKeyID = m_BlackBoard->GetKeyID("m_Target");

		m_BehaviorComponent->StartTree(*gCHar->GuardBehavior);
	}
}

