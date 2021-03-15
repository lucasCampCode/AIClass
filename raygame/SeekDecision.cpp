#include "SeekDecision.h"
#include "PursueBehavior.h"
#include "EvadeBehavior.h"
#include "WanderingBehavior.h"
#include "ComplexEnemy.h"
void SeekDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);
	if (enemy)
	{
		enemy->getPursue()->setEnabled(true);
		enemy->getWander()->setEnabled(false);
		enemy->getEvade()->setEnabled(false);
	}
}
