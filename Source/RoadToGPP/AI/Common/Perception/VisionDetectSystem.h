// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VisionDetectSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROADTOGPP_API UVisionDetectSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVisionDetectSystem();
	virtual ~UVisionDetectSystem() {};

	UPROPERTY(EditAnywhere, Category = "EntityToCheck")
		bool m_playerCheck;
	APawn * m_playerPawn;
	FVector m_playerLocation;
	bool	m_playerVisible;

	UPROPERTY(EditAnywhere, Category = "VisualSystem", meta = (ClampMin = "0.0", ClampMax = "90.0", UIMin = "0.0", UIMax = "0.0"))
		float m_degreeAngle;

	UPROPERTY(EditAnywhere, Category = "VisualSystem", meta = (ClampMin = "10.0", ClampMax = "1000.0", UIMin = "10.0", UIMax = "1000.0"))
		float m_maxForwardDist;

	UPROPERTY(EditAnywhere, Category = "VisualSystem")
		bool m_DebugCone;

	UPROPERTY(EditAnywhere, Category = "VisualSystem")
		FVector m_offSetToEye;

	float m_radiusAngle;
	float m_realMaxDist;
	FVector m_eyePoint;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
