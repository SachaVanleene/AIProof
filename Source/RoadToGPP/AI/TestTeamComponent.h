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

public:	
	// Sets default values for this component's properties
	UTestTeamComponent();

	UPROPERTY(EditAnywhere, Category = "Group")
	TArray<AActor *> teamComposition;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddMate(AActor * newMate) { teamComposition.Add(newMate); };
	const TArray<AActor *> & GetTeam() { return teamComposition; };
		
	
};
