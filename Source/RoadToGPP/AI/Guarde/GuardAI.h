// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GuardAI.generated.h"

/**
 * 
 */
UCLASS()
class ROADTOGPP_API AGuardAI : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(transient)
		class UBlackboardComponent * m_BlackBoard;

	UPROPERTY(transient)
		class UBehaviorTreeComponent * m_BehaviorComponent;
	

private:
	APawn * m_Pawn;
	uint8 m_EnnemyKeyID;
public :

	AGuardAI();

	virtual void Possess(APawn* InPawn) override;

	inline uint8 GetEnnemeyKeyID() { return m_EnnemyKeyID; };
	inline APawn * GetAssociatedPawn() { return m_Pawn; };
};
