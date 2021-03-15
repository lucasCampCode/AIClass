#include "HealthDecision.h"
#include "ComplexEnemy.h"
void HealthDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);
	if (enemy)
		if (checkCondition(agent,deltaTime))
			getLeft()->makeDecision(agent, deltaTime);
		else
			getRight()->makeDecision(agent, deltaTime);
}

bool HealthDecision::checkCondition(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);
	if (enemy)
		return enemy->getHealth() > 5;
}
