// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestTeamComponent.h"
#include <vector>
#include <string>
#include <list>
#include "GameFramework/CharacterMovementComponent.h"
#include "SteeringComponent.generated.h"


//--------------------------- Constants ----------------------------------

//the radius of the constraining circle for the wander behavior
const double WanderRad = 1.2;
//distance the wander circle is projected in front of the agent
const double WanderDist = 2.0;
//the maximum amount of displacement along the circle each frame
const double WanderJitterPerSec = 1.0;

class UTestTeamComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROADTOGPP_API USteeringComponent : public UActorComponent
{
	GENERATED_BODY()

private : 

	enum behavior_type
	{
		none = 0x00000,
		seek = 0x00002,
		arrive = 0x00008,
		wander = 0x00010,
		cohesion = 0x00020,
		separation = 0x00040,
		alignment = 0x00080,
		follow = 0x00100,
		wall_avoidance = 0x00200,
	};

	UPROPERTY(EditAnywhere, Category = "Steering|SteeringToActivate")
		bool seek_activated;

	UPROPERTY(EditAnywhere, Category = "Steering|SteeringToActivate")
		bool arrive_activated;

	UPROPERTY(EditAnywhere, Category = "Steering|SteeringToActivate")
		bool wander_activated;

	UPROPERTY(EditAnywhere, Category = "Steering|SteeringToActivate")
		bool cohesion_activated;

	UPROPERTY(EditAnywhere, Category = "Steering|SteeringToActivate")
		bool separation_activated;

	UPROPERTY(EditAnywhere, Category = "Steering|SteeringToActivate")
		bool alignment_activated;

	UPROPERTY(EditAnywhere, Category = "Steering|SteeringToActivate")
		bool follow_activated;

	UPROPERTY(EditAnywhere, Category = "Steering|SteeringToActivate")
		bool wall_avoidance_activated;

	//a pointer to the owner of this instance
	AActor*     m_owner;

	//the steering force created by the combined effect of all
	//the selected behaviors
	FVector       m_vSteeringForce;

	//these can be used to keep track of friends, pursuers, or prey
	AActor * m_currentTarget;

	//Leader to follow
	AActor*  leader;

	//Movement Component
	UCharacterMovementComponent * m_movComponent;

	//Team
	UPROPERTY(EditAnywhere, Category = "Steering|ActorTeam")
		AActor * m_TeamActor;
	UTestTeamComponent * m_Team;

	//a vertex buffer to contain the feelers rqd for wall avoidance  
	std::vector<FVector> m_Feelers;

	//the length of the 'feeler/s' used in wall detection
	double                 m_dWallDetectionFeelerLength;


	//the current position on the wander circle the agent is
	//attempting to steer towards
	FVector     m_vWanderTarget;

	//explained above
	UPROPERTY(EditAnywhere, Category = "Steering|SteeringWanderParameter")
	double        m_dWanderJitter;
	UPROPERTY(EditAnywhere, Category = "Steering|SteeringWanderParameter")
	double        m_dWanderRadius;
	UPROPERTY(EditAnywhere, Category = "Steering|SteeringWanderParameter")
	double        m_dWanderDistance;


	//multipliers. These can be adjusted to effect strength of the  
	//appropriate behavior.
	UPROPERTY(EditAnywhere, Category = "Steering|SteeringWight")
	double        m_dWeightSeparation;
	UPROPERTY(EditAnywhere, Category = "Steering|SteeringWight")
	double		  m_dWeightCohesion;
	UPROPERTY(EditAnywhere, Category = "Steering|SteeringWight")
	double		  m_dWeightAlignment;
	UPROPERTY(EditAnywhere, Category = "Steering|SteeringWight")
	double        m_dWeightFollow;
	UPROPERTY(EditAnywhere, Category = "Steering|SteeringWight")
	double        m_dWeightWander;
	UPROPERTY(EditAnywhere, Category = "Steering|SteeringWight")
	double        m_dWeightWallAvoidance;
	UPROPERTY(EditAnywhere, Category = "Steering|SteeringWight")
	double        m_dWeightSeek;
	UPROPERTY(EditAnywhere, Category = "Steering|SteeringWight")
	double        m_dWeightArrive;


	//how far the agent can 'see'
	double        m_dViewDistance;

	//binary flags to indicate whether or not a behavior should be active
	int           m_iFlags;


	//Arrive makes use of these to determine how quickly a Raven_Bot
	//should decelerate to its target
	enum Deceleration { slow = 3, normal = 2, fast = 1 };

	//default
	Deceleration m_Deceleration;

	//is cell space partitioning to be used or not?
	bool          m_bCellSpaceOn;

	//this function tests if a specific bit of m_iFlags is set
	bool      On(behavior_type bt) { return (m_iFlags & bt) == bt; }

	bool      AccumulateForce(FVector &sf, const FVector& ForceToAdd);

	//creates the antenna utilized by the wall avoidance behavior
	//void      CreateFeelers();



	/* .......................................................

					 BEGIN BEHAVIOR DECLARATIONS

	   .......................................................*/


	   //this behavior moves the agent towards a target position
	FVector Seek(const FVector &target);

	//this behavior is similar to seek but it attempts to arrive 
	//at the target with a zero velocity
	FVector Arrive(const FVector    &target,
		const Deceleration deceleration);

	//this behavior makes the agent wander about randomly
	FVector Wander();

	//this returns a steering force which will keep the agent away from any
	//walls it may encounter
	//FVector WallAvoidance(const std::vector<Wall2D*> &walls);

	FVector Cohesion(const TArray<AActor*>&agents);
	FVector Separation(const TArray<AActor*>&agents);
	FVector Alignment(const TArray<AActor*>&agents);
	FVector Follow(AActor* agents);


	/* .......................................................

					   END BEHAVIOR DECLARATIONS

	  .......................................................*/

	  //calculates and sums the steering forces from any active behaviors
	FVector CalculatePrioritized();

public:	
	// Sets default values for this component's properties
	USteeringComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	USteeringComponent(AActor* agent);

	virtual ~USteeringComponent() { };

	//calculates and sums the steering forces from any active behaviors
	//FVector Calculate();

	//calculates the component of the steering force that is parallel
	//with the Raven_Bot heading
	double    ForwardComponent();

	//calculates the component of the steering force that is perpendicuar
	//with the Raven_Bot heading
	double    SideComponent();

	FVector  Force()const { return m_vSteeringForce; }

	void SeekOn() { seek_activated = true; }
	void ArriveOn() { arrive_activated = true; }
	void WanderOn() { wander_activated = true; }
	void SeparationOn() { separation_activated = true; }
	void CohesionOn() { cohesion_activated = true; }
	void FollowLeaderOn(AActor* l) { follow_activated = true; leader = l; }
	void AlignmentOn() { alignment_activated = true; }
	void WallAvoidanceOn() { wall_avoidance_activated = true; }

	void SeekOff() { if (seek_activated)   seek_activated = false; }
	void ArriveOff() { if (arrive_activated) arrive_activated = false; }
	void WanderOff() { if (wander_activated) wander_activated = false; }
	void SeparationOff() { if (separation_activated) separation_activated = false; }
	void CohesionOff() { if (cohesion_activated) cohesion_activated = false; }
	void FollowLeaderOff() { if (follow_activated) follow_activated = true; }
	void AlignmentOff() { if (alignment_activated) alignment_activated = false; }
	void WallAvoidanceOff() { if (wall_avoidance_activated) wall_avoidance_activated = false; }

	bool SeekIsOn() { return seek_activated; }
	bool ArriveIsOn() { return arrive_activated; }
	bool WanderIsOn() { return wander_activated; }
	bool SeparationIsOn() { return separation_activated; }
	bool CohesionIsOn() { return cohesion_activated; }
	bool FollowLeaderIsOn() { return follow_activated; }
	bool AlignmentIsOn() { return alignment_activated; }
	bool WallAvoidanceIsOn() { return wall_avoidance_activated; }

	const std::vector<FVector>& GetFeelers()const { return m_Feelers; }

	double WanderJitter()const { return m_dWanderJitter; }
	double WanderDistance()const { return m_dWanderDistance; }
	double WanderRadius()const { return m_dWanderRadius; }

	double SeparationWeight()const { return m_dWeightSeparation; }
	
};
