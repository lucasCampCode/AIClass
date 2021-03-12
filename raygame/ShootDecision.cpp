#include "ShootDecision.h"
#include "complexEnemy.h"
#include "Game.h"
#include "EnemyBullet.h"
#include "Agent.h"
void ShootDecision::makeDecision(Agent* agent, float deltaTime)
{
    ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);
    m_timer += deltaTime;
    if (m_timer > 1)
    {
        if (enemy)
        {
            Game::getCurrentScene()->addActor(new EnemyBullet(
                agent->getWorldPosition().x, agent->getWorldPosition().y, 1, "Images/bullet.png", 5, agent->getForward() * 2));
        }
        else {
            Game::getCurrentScene()->addActor(new Bullet(
                agent->getWorldPosition().x, agent->getWorldPosition().y, 1, "Images/bullet.png", 5, agent->getForward() * 5));
        }
        m_timer = 0;
    }
}
