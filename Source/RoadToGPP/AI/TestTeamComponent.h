// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "list"
#include "TestTeamComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROADTOGPP_API UTestTeamComponent : public UActorComponent
{
	GENERATED_BODY()

private:
		std::list<AActor *> teamComposition;

public:	
	// Sets default values for this component's properties
	UTestTeamComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddMate(AActor * newMate) { teamComposition.push_back(newMate); };
	const std::list<AActor *> & GetTeam() { return teamComposition; };
		
	
};
