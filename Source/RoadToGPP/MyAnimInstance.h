// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROADTOGPP_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public :

	UMyAnimInstance() : isWalking(false), m_owner(nullptr), m_isIni(false) { };

protected:

	friend class UBTTask_LookingAround;

	float time{ 0 };

	/*True means that we're currently in air - or falling*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isWalking;

	/*Holds the current speed of our character*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isLookingAround;

	/*Updates the above properties*/
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
		void UpdateAnimationProperties();

	AActor * m_owner;
	bool m_isIni;

	virtual void NativeUpdateAnimation()
	{
		UpdateAnimationProperties();
	}

	inline void Initailize()
	{
		if (!m_isIni)
		{
			m_owner = GetOwningActor();
			m_isIni = true;
		}
	}

};