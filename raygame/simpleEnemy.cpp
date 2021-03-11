#include "SimpleEnemy.h"
#include "SeekBehavior.h"
#include "WanderingBehavior.h"
#include "Player.h"
bool SimpleEnemy::checkTargetInSight()
{
    
    if (getTarget() == nullptr)
        return false;

    MathLibrary::Vector2 velocity = getTarget()->getWorldPosition() - getWorldPosition();
    MathLibrary::Vector2 direction = velocity.getNormalized();
    float magnitude = velocity.getMagnitude();
    float dotProduct = MathLibrary::Vector2::dotProduct(getForward(), direction);
    //check if the angle is greater than the enemies viewing angle
    if (acos(dotProduct) < 0.75f)
        return true;
    return false;
}

void SimpleEnemy::onCollision(Actor* other)
{
    //check to see if the enemy ran into the player
    Player* player = dynamic_cast<Player*>(other); 
    //if the enemy has run into the player ,deal damage to player
    if (player)
    {
        player->takeDamage(getDamage());
        //if the player's health is less than 0, set the target to be nullptr
        if (player->getHealth() <= 0)
        {
            setTarget(nullptr);
        }
    }
}

void SimpleEnemy::start()
{
    Enemy::start();

    m_enemyState = WANDER;

    m_seek = getBehavior<SeekBehavior>();
    m_wander = getBehavior<WanderingBehavior>();

    setTarget(Enemy::getTarget());
}

void SimpleEnemy::update(float deltaTime)
{
    if (checkTargetInSight())
        m_enemyState = SEEK;
    else
        m_enemyState = WANDER;
    switch (m_enemyState)
    {
    case WANDER:
        m_wander->setForceScale(5);
        m_seek->setForceScale(0);
        break;
    case SEEK:
        m_seek->setForceScale(10);
        m_wander->setForceScale(0);
        break;
    default:
        break;
    }
    Enemy::update(deltaTime);
}

void SimpleEnemy::setTarget(Actor* agent)
{
    Enemy::setTarget(agent);
    m_seek->setTarget(agent);
}
