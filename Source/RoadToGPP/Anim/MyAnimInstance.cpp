// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

void UMyAnimInstance::UpdateAnimationProperties()
{
	Initailize();
	if (m_owner->GetVelocity().Size() >= 0.0f)
	{
		isWalking = true;
	}
	else
	{
		isWalking = false;
	}
}

