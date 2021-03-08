#include "simpleEnemy.h"
#include "SeekBehavior.h"
#include "WanderingBehavior.h"
bool simpleEnemy::checkTargetInSight()
{
    
    if (getTarget() == nullptr)
        return false;

    MathLibrary::Vector2 velocity = getTarget()->getWorldPosition() - getWorldPosition();
    MathLibrary::Vector2 direction = velocity.getNormalized();
    float magnitude = velocity.getMagnitude();
    float dotProduct = MathLibrary::Vector2::dotProduct(getForward(), direction);
    acos(dotProduct);
    //check if the angle is greater than the enemies viewing angle
    if (acos(dotProduct) < 0.5)
        return true;
    return false;
}

void simpleEnemy::onCollision(Actor* other)
{
    //check to see if the enemy ran into the player
    //if the enemy has run into the player ,deal damage to player
    //if the player's health is less than 0, set the target to be nullptr
}

void simpleEnemy::start()
{
    Enemy::start();

    m_enemyState = WANDER;

    m_seek = getBehavior<SeekBehavior>();
    m_wander = getBehavior<WanderingBehavior>();

    setTarget(Enemy::getTarget());
}

void simpleEnemy::update(float deltaTime)
{
}

void simpleEnemy::setTarget(Actor* agent)
{
}
