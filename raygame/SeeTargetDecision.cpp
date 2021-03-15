#include "SeeTargetDecision.h"
#include "Enemy.h"
#include <Vector2.h>
SeeTargetDecision::SeeTargetDecision(Decision* left, Decision* right, float maxAngle): ABDecision(left,right)
{
	m_maxAngle = maxAngle;
}

void SeeTargetDecision::makeDecision(Agent* agent, float deltaTime)
{
    Enemy* enemy = dynamic_cast<Enemy*>(agent);
    if (enemy)
        if (checkCondition(agent, deltaTime))
            getLeft()->makeDecision(agent, deltaTime);
        else
            getRight()->makeDecision(agent, deltaTime);
}

bool SeeTargetDecision::checkCondition(Agent* agent, float deltaTime)
{
    Enemy* enemy = dynamic_cast<Enemy*>(agent);
    
    if (enemy->getTarget() == nullptr)
        return false;

    MathLibrary::Vector2 velocity = enemy->getTarget()->getWorldPosition() - enemy->getWorldPosition();
    MathLibrary::Vector2 direction = velocity.getNormalized();
    float dotProduct = MathLibrary::Vector2::dotProduct(enemy->getForward(), direction);
    //check if the angle is greater than the enemies viewing angle
    if (acos(dotProduct) < m_maxAngle)
        return true;
    return false;
}
