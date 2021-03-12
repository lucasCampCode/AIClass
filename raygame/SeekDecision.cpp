#include "SeekDecision.h"
#include "SeekBehavior.h"
#include "WanderingBehavior.h"
#include "ComplexEnemy.h"
void SeekDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);
	if (enemy)
	{
		enemy->setSeekForce(10);
		enemy->setWanderForce(0);
	}
}
