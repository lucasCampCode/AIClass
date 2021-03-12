
#include "Bullet.h"
class EnemyBullet :
    public Bullet
{
    using Bullet::Bullet;
    void onCollision(Actor* actor) override;
};
