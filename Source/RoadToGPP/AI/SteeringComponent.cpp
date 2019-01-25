// Fill out your copyright notice in the Description page of Project Settings.

#include "SteeringComponent.h"
#include "UtilsR/UltisRaven.h"

// Sets default values for this component's properties
USteeringComponent::USteeringComponent(AActor* agent) :
m_owner(agent),
m_iFlags(0),
m_dWeightSeparation(10.0),
m_dWeightAlignment(0.7), //codé en dur, peu mieux faire
m_dWeightCohesion(0.7),
m_dWeightFollow(0.2),
m_dWeightWander(1.0),
m_dWeightWallAvoidance(10.0),
m_dViewDistance(15.0),
m_dWallDetectionFeelerLength(25.0),
m_Feelers(3),
m_Deceleration(normal),
m_dWanderDistance(WanderDist),
m_dWanderJitter(WanderJitterPerSec),
m_dWanderRadius(WanderRad),
m_dWeightSeek(0.5),
m_dWeightArrive(1.0),
m_bCellSpaceOn(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	m_movComponent = m_owner->FindComponentByClass<UCharacterMovementComponent>();

	m_Team = m_owner->FindComponentByClass<UTestTeamComponent>();


	//stuff for the wander behavior
	double theta = (double)rand() / (double)RAND_MAX * 2*PI;

	//create a vector to a target position on the wander circle
	m_vWanderTarget = FVector(m_dWanderRadius * cos(theta),
		m_dWanderRadius * sin(theta), 0.0);

}

// Sets default values for this component's properties
USteeringComponent::USteeringComponent() :
	m_iFlags(0),
	m_dWeightSeparation(10.0),
	m_dWeightAlignment(0.7), //codé en dur, peu mieux faire
	m_dWeightCohesion(0.7),
	m_dWeightFollow(0.2),
	m_dWeightWander(1.0),
	m_dWeightWallAvoidance(10.0),
	m_dViewDistance(15.0),
	m_dWallDetectionFeelerLength(25.0),
	m_Feelers(3),
	m_Deceleration(normal),
	m_dWanderDistance(WanderDist),
	m_dWanderJitter(WanderJitterPerSec),
	m_dWanderRadius(WanderRad),
	m_dWeightSeek(1.0),
	m_dWeightArrive(1.0),
	m_bCellSpaceOn(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	//stuff for the wander behavior
	double theta = (double)rand() / (double)RAND_MAX * 2 * PI;

	//create a vector to a target position on the wander circle
	m_vWanderTarget = FVector(m_dWanderRadius * cos(theta),
							  m_dWanderRadius * sin(theta), 
						      0.0);

}



// Called when the game starts
void USteeringComponent::BeginPlay()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "begin play");
	Super::BeginPlay();
	m_owner = GetOwner();

	if (m_owner)
	{
		m_movComponent = m_owner->FindComponentByClass<UCharacterMovementComponent>();

		m_Team = m_owner->FindComponentByClass<UTestTeamComponent>();
	}
	m_currentTarget = GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...
	
}


// Called every frame
void USteeringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (m_currentTarget)
	{
		
;		FVector force = CalculatePrioritized();
		m_movComponent->AddForce(force);
		/*FVector test = m_owner->GetActorLocation();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("VECTOR %.2f, %.2f, %.2f"), test.X, test.Y, test.Z));*/
		//UE_LOG(LogTemp, Warning, TEXT("Apply force 2 "));
	}
	// ...
}


/////////////////////////////////////////////////////////////////////////////// CALCULATE METHODS 


//----------------------- Calculate --------------------------------------
//
//  calculates the accumulated steering force according to the method set
//  in m_SummingMethod
//------------------------------------------------------------------------
/*FVector USteeringComponent::Calculate()
{
	//reset the steering force
	m_vSteeringForce.Set(0.0, 0.0, 0.0);

	//tag neighbors if any of the following 3 group behaviors are switched on
	if (On(separation))
	{
		m_pWorld->TagRaven_BotsWithinViewRange(m_owner, m_dViewDistance);
	}

	m_vSteeringForce = CalculatePrioritized();

	return m_vSteeringForce;
}*/

//------------------------- ForwardComponent -----------------------------
//
//  returns the forward component of the steering force
//------------------------------------------------------------------------
double USteeringComponent::ForwardComponent()
{
	return m_owner->GetActorForwardVector() | (m_vSteeringForce);
}

//--------------------------- SideComponent ------------------------------
//  returns the side component of the steering force
//------------------------------------------------------------------------
double USteeringComponent::SideComponent()
{
	return m_owner->GetActorRightVector() |(m_vSteeringForce);
}

//--------------------- AccumulateForce ----------------------------------
//
//  This function calculates how much of its max steering force the 
//  vehicle has left to apply and then applies that amount of the
//  force to add.
//------------------------------------------------------------------------
bool USteeringComponent::AccumulateForce(FVector &RunningTot,
	const FVector& ForceToAdd)
{
	//calculate how much steering force the vehicle has used so far
	double MagnitudeSoFar = RunningTot. Size();

	//calculate how much steering force remains to be used by this vehicle
	double MagnitudeRemaining = m_movComponent->GetMaxAcceleration() - MagnitudeSoFar;

	//return false if there is no more force left to use
	if (MagnitudeRemaining <= 0.0) return false;

	//calculate the magnitude of the force we want to add
	double MagnitudeToAdd = ForceToAdd. Size();

	//if the magnitude of the sum of ForceToAdd and the running total
	//does not exceed the maximum force available to this vehicle, just
	//add together. Otherwise add as much of the ForceToAdd vector is
	//possible without going over the max.
	if (MagnitudeToAdd < MagnitudeRemaining)
	{
		RunningTot += ForceToAdd;
	}

	else
	{
		MagnitudeToAdd = MagnitudeRemaining;

		//add it to the steering force
		RunningTot += (ForceToAdd.GetUnsafeNormal() * MagnitudeToAdd);
	}

	return true;
}



//---------------------- CalculatePrioritized ----------------------------
//
//  this method calls each active steering behavior in order of priority
//  and acumulates their forces until the max steering force magnitude
//  is reached, at which time the function returns the steering force 
//  accumulated to that  point
//------------------------------------------------------------------------
FVector USteeringComponent::CalculatePrioritized()
{
	FVector force;
	/*
	if (On(wall_avoidance))
	{
		force = WallAvoidance(m_pWorld->GetMap()->GetWalls()) *
			m_dWeightWallAvoidance;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}*/

	m_vSteeringForce = FVector::ZeroVector;
	//these next three can be combined for flocking behavior (wander is
	//also a good behavior to add into this mix)

	if (SeparationIsOn())
	{
		force = Separation(m_Team->GetTeam()) * m_dWeightSeparation;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (CohesionIsOn())
	{
		force = Cohesion(m_Team->GetTeam()) * m_dWeightCohesion;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (AlignmentIsOn())
	{
		force = Alignment(m_Team->GetTeam()) * m_dWeightAlignment;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (FollowLeaderIsOn())
	{
		force = Follow(m_currentTarget) * m_dWeightFollow;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (SeekIsOn())
	{
		force = Seek(m_currentTarget->GetActorLocation()) * m_dWeightSeek;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (ArriveIsOn())
	{
		force = Arrive(m_currentTarget->GetActorLocation(), m_Deceleration) * m_dWeightArrive;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (WanderIsOn())
	{
		force = Wander() * m_dWeightWander;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	return m_vSteeringForce;
}


/////////////////////////////////////////////////////////////////////////////// START OF BEHAVIORS

//------------------------------- Seek -----------------------------------
//
//  Given a target, this behavior returns a steering force which will
//  direct the agent towards the target
//------------------------------------------------------------------------
FVector USteeringComponent::Seek(const FVector &target)
{

	FVector DesiredVelocity = (target - m_owner-> GetActorLocation()).GetUnsafeNormal()
		* m_movComponent->MaxWalkSpeed;

	return (DesiredVelocity - m_movComponent->Velocity);
}


//--------------------------- Arrive -------------------------------------
//
//  This behavior is similar to seek but it attempts to arrive at the
//  target with a zero velocity
//------------------------------------------------------------------------
FVector USteeringComponent::Arrive(const FVector    &target,
	const Deceleration deceleration)
{
	FVector ToTarget = target - m_owner-> GetActorLocation();

	//calculate the distance to the target
	double dist = ToTarget. Size();

	if (dist > 0.0f)
	{
		//because Deceleration is enumerated as an int, this value is required
		//to provide fine tweaking of the deceleration..
		const double DecelerationTweaker = 0.3;

		//calculate the speed required to reach the target given the desired
		//deceleration
		double speed = dist / ((double)deceleration * DecelerationTweaker);

		//make sure the velocity does not exceed the max
		speed = fmin(speed, m_movComponent->MaxWalkSpeed);

		//from here proceed just like Seek except we don't need to normalize 
		//the ToTarget vector because we have already gone to the trouble
		//of calculating its length: dist. 
		FVector DesiredVelocity = ToTarget * speed / dist;

		return (DesiredVelocity - m_movComponent->Velocity);
	}

	return FVector(0.0f, 0.0f, 0.0f);
}



//--------------------------- Wander -------------------------------------
//
//  This behavior makes the agent wander about randomly
//------------------------------------------------------------------------
FVector USteeringComponent::Wander()
{
	//first, add a small random vector to the target's position
	m_vWanderTarget += FVector((double)rand() / (double)RAND_MAX * m_dWanderJitter,
		(double)rand() / (double)RAND_MAX * m_dWanderJitter, (double)rand() / (double)RAND_MAX * m_dWanderJitter);

	//reproject this new vector back on to a unit circle
	m_vWanderTarget.Normalize();

	//increase the length of the vector to the same as the radius
	//of the wander circle
	m_vWanderTarget *= m_dWanderRadius;

	//move the target into a position WanderDist in front of the agent
	FVector target = m_vWanderTarget + FVector(m_dWanderDistance, 0.0f, 0.0f);

	FVector  worldTarget = m_owner->GetTransform().TransformPosition(target);
	//project the target into world space
	/*FVector Target = PointToWorldSpace(target,
		m_owner->GetActorForwardVector(),
		m_owner->GetActorRightVector(),
		m_owner-> GetActorLocation());*/

	FVector steer = worldTarget - m_owner->GetActorLocation();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("VECTOR %.2f, %.2f, %.2f"), steer.X, steer.Y, steer.Z));
	//UE_LOG(LogTemp, Log, TEXT("VECTOR %.2f, %.2f, %.2f"), worldTarget.X, worldTarget.Y, worldTarget.Z);

	//and steer towards it
	return steer;
}

/*
//--------------------------- WallAvoidance --------------------------------
//
//  This returns a steering force that will keep the agent away from any
//  walls it may encounter
//------------------------------------------------------------------------
FVector USteeringComponent::WallAvoidance(const vector<Wall2D*> &walls)
{
	//the feelers are contained in a std::vector, m_Feelers
	CreateFeelers();

	double DistToThisIP = 0.0;
	double DistToClosestIP = MaxDouble;

	//this will hold an index into the vector of walls
	int ClosestWall = -1;

	FVector SteeringForce,
		point,         //used for storing temporary info
		ClosestPoint;  //holds the closest intersection point

//examine each feeler in turn
	for (unsigned int flr = 0; flr < m_Feelers.size(); ++flr)
	{
		//run through each wall checking for any intersection points
		for (unsigned int w = 0; w < walls.size(); ++w)
		{
			if (LineIntersection2D(m_owner-> GetActorLocation(),
				m_Feelers[flr],
				walls[w]->From(),
				walls[w]->To(),
				DistToThisIP,
				point))
			{
				//is this the closest found so far? If so keep a record
				if (DistToThisIP < DistToClosestIP)
				{
					DistToClosestIP = DistToThisIP;

					ClosestWall = w;

					ClosestPoint = point;
				}
			}
		}//next wall


		//if an intersection point has been detected, calculate a force  
		//that will direct the agent away
		if (ClosestWall >= 0)
		{
			//calculate by what distance the projected position of the agent
			//will overshoot the wall
			FVector OverShoot = m_Feelers[flr] - ClosestPoint;

			//create a force in the direction of the wall normal, with a 
			//magnitude of the overshoot
			SteeringForce = walls[ClosestWall]->Normal() * OverShoot. Size();
		}

	}//next feeler

	return SteeringForce;
}

//------------------------------- CreateFeelers --------------------------
//
//  Creates the antenna utilized by WallAvoidance
//------------------------------------------------------------------------
void USteeringComponent::CreateFeelers()
{
	//feeler pointing straight in front
	m_Feelers[0] = m_owner-> GetActorLocation() + m_dWallDetectionFeelerLength *
		m_owner->Heading() * m_owner->Speed();

	//feeler to left
	FVector temp = m_owner->Heading();
	Vec2DRotateAroundOrigin(temp, HalfPi * 3.5);
	m_Feelers[1] = m_owner-> GetActorLocation() + m_dWallDetectionFeelerLength / 2.0 * temp;

	//feeler to right
	temp = m_owner->Heading();
	Vec2DRotateAroundOrigin(temp, HalfPi * 0.5);
	m_Feelers[2] = m_owner-> GetActorLocation() + m_dWallDetectionFeelerLength / 2.0 * temp;
}

*/
//---------------------------- Separation --------------------------------
//
// this calculates a force repelling from the other neighbors
//------------------------------------------------------------------------
FVector USteeringComponent::Separation(const std::list<AActor*>& neighbors)
{
	//iterate through all the neighbors and calculate the vector from the
	FVector SteeringForce;

	std::list<AActor*>::const_iterator it = neighbors.begin();
	for (it; it != neighbors.end(); ++it)
	{
		//make sure this agent isn't included in the calculations and that
		//the agent being examined is close enough. ***also make sure it doesn't
		//include the evade target ***
		if (*it != m_owner) 
		{
			FVector ToAgent = m_owner-> GetActorLocation() - (*it)-> GetActorLocation();

			//scale the force inversely proportional to the agents distance  
			//from its neighbor.
			SteeringForce += ToAgent.GetUnsafeNormal() / ToAgent. Size();
		}
	}

	return SteeringForce;
}

FVector USteeringComponent::Cohesion(const std::list<AActor*> &agents)
{
	//first find the center of mass of all the agents
	FVector CenterOfMass, SteeringForce;

	int NeighborCount = 0;

	std::list<AActor*>::const_iterator it = agents.begin();
	for (it; it != agents.end(); ++it)
	{
		//make sure this agent isn't included in the calculations and that
		//the agent being examined is close enough. ***also make sure it doesn't
		//include the evade target ***
		if (*it != m_owner)
		{
			CenterOfMass += (*it)-> GetActorLocation();

			++NeighborCount;
		}
	}

	if (NeighborCount > 0)
	{
		//the center of mass is the average of the sum of positions
		CenterOfMass /= (double)NeighborCount;

		//now seek towards that position
		SteeringForce = Seek(CenterOfMass);
	}

	//the magnitude of cohesion is usually much larger than separation or
	//allignment so it usually helps to normalize it.
	return SteeringForce.GetUnsafeNormal();
}

FVector USteeringComponent::Alignment(const std::list<AActor*> &agents)
{
	//used to record the average heading of the neighbors
	FVector AverageHeading;

	//used to count the number of vehicles in the neighborhood
	int    NeighborCount = 0;

	std::list<AActor*>::const_iterator it = agents.begin();
	for (it; it != agents.end(); ++it)
	{
		//make sure this agent isn't included in the calculations and that
		//the agent being examined is close enough. ***also make sure it doesn't
		//include the evade target ***
		if (*it != m_owner)
		{
			AverageHeading += (*it)->GetActorForwardVector();

			++NeighborCount;
		}
	}

	//if the neighborhood contained one or more vehicles, average their
	//heading vectors.
	if (NeighborCount > 0)
	{
		AverageHeading /= (double)NeighborCount;

		AverageHeading -= m_owner->GetActorForwardVector();
	}

	return AverageHeading;
}

FVector USteeringComponent::Follow(AActor* leader)
{
	FVector ToEvader = leader-> GetActorLocation() - m_owner-> GetActorLocation();

	double RelativeHeading = m_owner->GetActorForwardVector() | (leader->GetActorForwardVector());

	if ((FVector::DotProduct(ToEvader, (m_owner->GetActorForwardVector())) > 0.0f ) &&
		(RelativeHeading < -0.95))  //acos(0.95)=18 degs
	{
		return Seek(leader-> GetActorLocation());
	}

	//Not considered ahead so we predict where the evader will be.

	//the lookahead time is propotional to the distance between the evader
	//and the pursuer; and is inversely proportional to the sum of the
	//agent's velocities
	double LookAheadTime = ToEvader.Size() /
		(m_movComponent->GetMaxSpeed() + leader->GetVelocity().Size());

	//now seek to the predicted future position of the evader
	return Seek((leader-> GetActorLocation() + leader->GetVelocity()) * LookAheadTime);
}

