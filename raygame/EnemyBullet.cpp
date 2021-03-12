#include "EnemyBullet.h"
#include "Game.h"
#include "Player.h"

void EnemyBullet::onCollision(Actor* actor)
{
	Player* player = dynamic_cast<Player*>(actor);

	if (player && actor != this)
	{
		Game::destroy(actor);
		Game::destroy(this);
	}
}
