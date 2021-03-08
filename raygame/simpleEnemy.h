#pragma once
#include "Enemy.h"
enum EnemyState {
    WANDER,
    SEEK
};

class WanderingBehavior;
class SeekBehavior;

class simpleEnemy :
    public Enemy
{
    using Enemy::Enemy;
    bool checkTargetInSight();

    void onCollision(Actor* other) override;
    void start() override;
    void update(float deltaTime) override;

    void setTarget(Actor* agent) override;
private:
    EnemyState m_enemyState;
    WanderingBehavior* m_wander;
    SeekBehavior* m_seek;
};

