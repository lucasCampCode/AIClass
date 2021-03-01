#include "SeekBehavior.h"
#include "Agent.h"
MathLibrary::Vector2 SeekBehavior::calculateForce(Agent* agent)
{
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());
	
	

	return MathLibrary::Vector2();
}
