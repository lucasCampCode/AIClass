#include "Bullet.h"
#include "Game.h"
#include "Player.h"

Bullet::Bullet(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, MathLibrary::Vector2 velocity,Actor* host) : Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
	setVelocity(velocity);
	m_host = host;
}

void Bullet::update(float deltaTime)
{
	Actor::update(deltaTime);

	if (getWorldPosition().x < 0 || getWorldPosition().x > 50
		|| getWorldPosition().y < 0 || getWorldPosition().y > 30)
		Game::destroy(this);

}

void Bullet::onCollision(Actor* actor)
{
	Player* player = dynamic_cast<Player*>(actor);
	Character* other = dynamic_cast<Character*>(actor);
	if (!player && actor != this)
	{
		if(other)
 			other->takeDamage(((Character*)getHost())->getDamage());
		Game::destroy(this);
	}
}
