#include "PursueBehavior.h"
#include "Agent.h"
#include "Actor.h"
PursueBehavior::PursueBehavior()
{
	m_target = nullptr;
	setForceScale(1);
}
PursueBehavior::PursueBehavior(Actor* target, float seekForce)
{
	m_target = target;
	setForceScale(seekForce);
}
MathLibrary::Vector2 PursueBehavior::calculateForce(Agent* agent)
{
	//gets the position infront of the target to pursue
	MathLibrary::Vector2 aheadOftarget = m_target->getWorldPosition() + m_target->getVelocity();
	//finds the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(aheadOftarget - agent->getWorldPosition());
	//scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();
	//subtreact the desired velocity to the agents velocity
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}

void PursueBehavior::update(Agent* agent, float deltaTime)
{
	//if the agent isn't null, calculate a new force and aplly it to the agent
	if (agent)
		agent->addForce(calculateForce(agent));
}