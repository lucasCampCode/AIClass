#include "ABDecision.h"

void ABDecision::makeDecision(Agent* agent, float deltaTime)
{
	if (m_choice)
		m_left->makeDecision(agent, deltaTime);
	else
		m_right->makeDecision(agent, deltaTime);
}
