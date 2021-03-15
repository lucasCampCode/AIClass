#pragma once
#include "Actor.h"

class Bullet : public Actor
{
public:
	Bullet(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, MathLibrary::Vector2 velocity,Actor* host);
	void update(float deltaTime) override;
	void onCollision(Actor* actor) override;
	Actor* getHost() { return m_host; }
	void setHost(Actor* host) { m_host = host; }
private:
	Actor* m_host;
};

