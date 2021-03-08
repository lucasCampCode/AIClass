#include "EvadeBehavior.h"
#include "Agent.h"
#include "Actor.h"
EvadeBehavior::EvadeBehavior()
{
	m_target = nullptr;
	m_seekForce = 1;
}
EvadeBehavior::EvadeBehavior(Actor* target, float seekForce)
{
	m_target = target;
	m_seekForce = seekForce;
}
MathLibrary::Vector2 EvadeBehavior::calculateForce(Agent* agent)
{
	//gets the position infront of the target to pursue
	MathLibrary::Vector2 aheadOftarget = m_target->getWorldPosition() + m_target->getVelocity();
	//finds the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(agent->getWorldPosition() - aheadOftarget);
	//scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * m_seekForce;
	//subtreact the desired velocity to the agents velocity
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}

void EvadeBehavior::update(Agent* agent, float deltaTime)
{
	//if the agent isn't null, calculate a new force and aplly it to the agent
	if (agent)
		agent->addForce(calculateForce(agent));
}
