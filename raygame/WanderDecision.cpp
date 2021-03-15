#include "WanderDecision.h"
#include "PursueBehavior.h"
#include "EvadeBehavior.h"
#include "WanderingBehavior.h"
#include "ComplexEnemy.h"
void WanderDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);
	if (enemy) 
	{
		enemy->getPursue()->setEnabled(false);
		enemy->getWander()->setEnabled(true);
		enemy->getEvade()->setEnabled(false);
	}
}
