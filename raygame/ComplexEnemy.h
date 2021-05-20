#pragma once
#include "Enemy.h"
//class types to shut the compiler up
class PursueBehavior;
class WanderingBehavior;
class DecisionBehavior;
class EvadeBehavior;
class ABDecision;

class ComplexEnemy :
    public Enemy
{
public:
    ~ComplexEnemy();
    using Enemy::Enemy;
    void start() override;
    void update(float deltaTime)override;
    void setTarget(Actor* agent) override;

    PursueBehavior* getPursue() { return m_pursue; }
    WanderingBehavior* getWander() { return m_wander; }
    EvadeBehavior* getEvade() { return m_evade; }
private:
    PursueBehavior* m_pursue;
    DecisionBehavior* m_decision;
    WanderingBehavior* m_wander;
    EvadeBehavior* m_evade;
};

