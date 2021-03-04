#include "WanderingBehavior.h"
#include "Agent.h"
#include "Actor.h"
#include <time.h>
WanderingBehavior::WanderingBehavior()
{
	m_seekForce = 1;
}

WanderingBehavior::WanderingBehavior( float seekForce)
{
	m_seekForce = seekForce;
}

MathLibrary::Vector2 WanderingBehavior::calculateForce(Agent* agent)
{
	srand(time(NULL));

	MathLibrary::Vector2 circleDialate = MathLibrary::Vector2::normalize(MathLibrary::Vector2((rand()% 3) - 1,(rand() % 3) - 1))*m_seekForce;
	MathLibrary::Vector2 circleOnAgent = circleDialate + agent->getWorldPosition();
	MathLibrary::Vector2 nextPoint = agent->getVelocity() + circleOnAgent;
	//finds the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(nextPoint - agent->getWorldPosition());
	//scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * m_seekForce;
	//subtreact the desired velocity to the agents velocity
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();
	return steeringForce;
}

void WanderingBehavior::update(Agent* agent, float deltaTime)
{
	//if the agent isn't null, calculate a new force and aplly it to the agent
	if (agent)
		agent->addForce(calculateForce(agent));
}
