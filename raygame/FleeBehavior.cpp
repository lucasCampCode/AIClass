#include "FleeBehavior.h"
#include "Agent.h"
#include "Actor.h"
FleeBehavior::FleeBehavior()
{
	m_target = nullptr;
	setForceScale(1);
}
FleeBehavior::FleeBehavior(Actor* target, float seekForce)
{
	m_target = target;
	setForceScale(seekForce);
}
MathLibrary::Vector2 FleeBehavior::calculateForce(Agent* agent)
{
	//finds the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(agent->getWorldPosition() - m_target->getWorldPosition());
	//scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();
	//subtreact the desired velocity to the agents velocity
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}

void FleeBehavior::update(Agent* agent, float deltaTime)
{
	//if the agent isn't null, calculate a new force and aplly it to the agent
	if (agent)
		agent->addForce(calculateForce(agent));
}