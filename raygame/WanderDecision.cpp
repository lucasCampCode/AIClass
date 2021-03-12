#include "WanderDecision.h"
#include "SeekBehavior.h"
#include "WanderingBehavior.h"
#include "ComplexEnemy.h"
void WanderDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);
	if (enemy) 
	{
		enemy->setSeekForce(0);
		enemy->setWanderForce(10);
	}
}
