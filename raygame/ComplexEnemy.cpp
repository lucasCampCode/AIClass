#include "ComplexEnemy.h"
#include "ABDecision.h"
#include "ShootDecision.h"
#include "WanderDecision.h"
#include "SeekDecision.h"
#include "SeekBehavior.h"
#include "WanderingBehavior.h"
bool ComplexEnemy::checkInSight(float maxAngle)
{
    if (getTarget() == nullptr)
        return false;

    MathLibrary::Vector2 velocity = getTarget()->getWorldPosition() - getWorldPosition();
    MathLibrary::Vector2 direction = velocity.getNormalized();
    float dotProduct = MathLibrary::Vector2::dotProduct(getForward(), direction);
    //check if the angle is greater than the enemies viewing angle
    if (acos(dotProduct) < maxAngle)
        return true;
    return false;
}
void ComplexEnemy::start()
{
    Enemy::start();
    //ai inizialization decisions
    WanderDecision* wander = new WanderDecision();
    ShootDecision* shoot = new ShootDecision();
    SeekDecision* seek = new SeekDecision();

    m_decision2 = new ABDecision(shoot,seek);
    m_decision1 = new ABDecision(m_decision2,wander);
    //retrives behavior from agent
    m_seek = getBehavior<SeekBehavior>();
    m_wander = getBehavior<WanderingBehavior>();
    //set target
    setTarget(Enemy::getTarget());
}

void ComplexEnemy::update(float deltaTime)
{
    m_decision1->setChoice(checkInSight(0.75f));
    m_decision2->setChoice(checkInSight(0.2f));

    m_decision1->makeDecision(this, deltaTime);

    Enemy::update(deltaTime);
}

void ComplexEnemy::setSeekForce(float force)
{
    m_seek->setForceScale(force);
}

void ComplexEnemy::setWanderForce(float force)
{
    m_wander->setForceScale(force);
}

void ComplexEnemy::setTarget(Actor* agent)
{
    Enemy::setTarget(agent);
    m_seek->setTarget(agent);
}
