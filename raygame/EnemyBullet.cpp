#include "EnemyBullet.h"
#include "Game.h"
#include "ComplexEnemy.h"
#include "Character.h"

void EnemyBullet::onCollision(Actor* actor)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(actor);
	Character* other = dynamic_cast<Character*>(actor);
	if (!enemy && actor != this)
	{
		if(other)
			other->takeDamage(((Character*)getHost())->getDamage());
		Game::destroy(this);
	}
}
