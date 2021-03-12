#include "ABDecision.h"

ABDecision::ABDecision(Decision* left, Decision* right)
{
	m_left = left;
	m_right = right;
}

void ABDecision::makeDecision(Agent* agent, float deltaTime)
{
	if (m_choice)
		m_left->makeDecision(agent, deltaTime);
	else
		m_right->makeDecision(agent, deltaTime);
}
