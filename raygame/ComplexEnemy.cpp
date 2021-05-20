#include "ComplexEnemy.h"
#include "DecisionBehavior.h"
#include "PursueBehavior.h"
#include "WanderingBehavior.h"
#include "EvadeBehavior.h"
#include "Game.h"
ComplexEnemy::~ComplexEnemy()
{
    Actor::~Actor();

    delete m_evade;
    delete m_wander;
    delete m_pursue;
}
void ComplexEnemy::start()
{
    Enemy::start();
    EvadeBehavior* evade = new EvadeBehavior(getTarget(), 10);
    WanderingBehavior* wander = new WanderingBehavior(5, 2);
    PursueBehavior* pursue = new PursueBehavior(getTarget(), 10);
    addBehavior(evade);
    addBehavior(wander);
    addBehavior(pursue);

    //retrives behavior from agent
    m_decision = getBehavior<DecisionBehavior>();
    m_pursue = getBehavior<PursueBehavior>();
    m_wander = getBehavior<WanderingBehavior>();
    m_evade = getBehavior<EvadeBehavior>();

    //set target
    setTarget(Enemy::getTarget());
}

void ComplexEnemy::update(float deltaTime)
{
    Enemy::update(deltaTime);
    if (getHealth() <= 0)
        Game::destroy(this);
}



void ComplexEnemy::setTarget(Actor* agent)
{
    Enemy::setTarget(agent);
    m_pursue->setTarget(agent);
    m_evade->setTarget(agent);
}
