// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

void UMyAnimInstance::UpdateAnimationProperties()
{
	if (movementSpeed >= 0)
	{
		isWalking = true;
	}
	else
	{
		isWalking = false;
	}
}

