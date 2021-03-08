#include "ArriveBehavior.h"
#include "Agent.h"
#include "Actor.h"
ArriveBehavior::ArriveBehavior()
{
	m_target = nullptr;
	setForceScale(1);
}
ArriveBehavior::ArriveBehavior(Actor* target, float seekForce)
{
	m_target = target;
	setForceScale(seekForce);
}
MathLibrary::Vector2 ArriveBehavior::calculateForce(Agent* agent)
{
	MathLibrary::Vector2 desiredVelocity;
	//gets the vector to the target
	MathLibrary::Vector2 toTarget = m_target->getWorldPosition() - agent->getWorldPosition();
	//finds the targets distance from agent;
	float distance = toTarget.getMagnitude();
	//finds the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(toTarget);
	if (distance > getForceScale())
		desiredVelocity = direction * agent->getMaxSpeed();
	else
		desiredVelocity = (direction * agent->getMaxSpeed()) * distance / getForceScale();

	//scale the direction vector by the seekForce
	//subtreact the desired velocity to the agents velocity
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}

void ArriveBehavior::update(Agent* agent, float deltaTime)
{
	//if the agent isn't null, calculate a new force and aplly it to the agent
	if (agent)
		agent->addForce(calculateForce(agent));
}

