#pragma once
#include "Enemy.h"
//class types to shut the compiler up
class SeekBehavior;
class WanderingBehavior;
class ABDecision;

class ComplexEnemy :
    public Enemy
{
public:
    using Enemy::Enemy;
    bool checkInSight(float maxAngle);

    void start() override;
    void update(float deltaTime) override;
    void setSeekForce(float force);
    void setWanderForce(float force);
    void setTarget(Actor* agent) override;
private:
    ABDecision* m_decision1;
    ABDecision* m_decision2;
    SeekBehavior* m_seek;
    WanderingBehavior* m_wander;
};

