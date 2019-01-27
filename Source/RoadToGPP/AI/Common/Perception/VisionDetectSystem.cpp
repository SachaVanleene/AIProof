// Fill out your copyright notice in the Description page of Project Settings.

#include "VisionDetectSystem.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"


// Sets default values for this component's properties
UVisionDetectSystem::UVisionDetectSystem() :
	m_playerLocation(FVector::ZeroVector),
	m_eyePoint(FVector::ZeroVector),
	m_playerPawn(nullptr),
	m_playerVisible(false),
	m_realMaxDist(10000),
	m_radiusAngle(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UVisionDetectSystem::BeginPlay()
{
	Super::BeginPlay();

	m_radiusAngle = FMath::DegreesToRadians(m_degreeAngle);
	m_realMaxDist = m_maxForwardDist / cos(m_radiusAngle);
}


//TODO : Bad
// Called every frame
void UVisionDetectSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_playerCheck && m_playerPawn == nullptr)
	{
		m_playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (m_playerPawn == nullptr)
		{
			//Error happened
			m_playerCheck = false;
		}
	}

	if (m_playerPawn != nullptr)
	{
		m_playerLocation = m_playerPawn->GetActorLocation();
		m_eyePoint = GetOwner()->GetActorLocation() + m_offSetToEye;
		FVector vectorEyeToPlayer((m_playerLocation - m_eyePoint).GetSafeNormal());
		FVector vectorEyeDirection = GetOwner()->GetActorForwardVector();
		/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("EyeDirection : %.2f, %.2f ,%.2f"), vectorEyeDirection.X, vectorEyeDirection.Y, vectorEyeDirection.Z));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("EyeToPlayer : %.2f, %.2f ,%.2f"), vectorEyeToPlayer.X, vectorEyeToPlayer.Y, vectorEyeToPlayer.Z));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("COS : %.2f"), FVector::DotProduct(vectorEyeToPlayer, vectorEyeDirection)));*/
		if (FVector::DotProduct(vectorEyeToPlayer, vectorEyeDirection) > cos(m_radiusAngle))
		{
			m_playerVisible = true;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Player Detected")));
		}
		if (m_DebugCone)
		{
			DrawDebugCone(GetWorld(), m_eyePoint, vectorEyeDirection, m_maxForwardDist, m_radiusAngle, m_radiusAngle, 8, FColor::Blue);
			DrawDebugLine(GetWorld(), m_eyePoint, m_playerLocation, FColor::Green);
			DrawDebugLine(GetWorld(), m_eyePoint, m_eyePoint + (GetOwner()->GetActorForwardVector()) * m_maxForwardDist, FColor::Magenta);
		}
	}
}

