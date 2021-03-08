#include "Agent.h"
#include "Behavior.h"

Agent::Agent() : Actor()
{
	m_force = { 0 ,0 };
	m_maxForce = 1;

}

Agent::Agent(float x, float y, float collisionRadius, char icon, float maxSpeed, float maxForce) 
	: Actor(x, y, collisionRadius, icon, maxSpeed)
{
	m_force = { 0 ,0 };
	m_maxForce = maxForce;
}

Agent::Agent(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed, float maxForce)
	: Actor(x, y, collisionRadius, sprite, maxSpeed)
{
	m_force = { 0 ,0 };
	m_maxForce = maxForce;
}

Agent::Agent(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float maxForce)
	: Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
	m_force = { 0 ,0 };
	m_maxForce = maxForce;
}

void Agent::update(float deltaTime)
{
	//resets force so its not constantly applied
	m_force = { 0,0 };

	//TO DO: update forces
	for (int i = 0; i < m_behaviors.size(); i++)
		m_behaviors[i]->update(this, deltaTime);

	//updates velocity with the new force
	setVelocity(getVelocity() + m_force * deltaTime);

	updateFacing();

	Actor::update(deltaTime);
}

void Agent::draw()
{
	for (int i = 0; i < m_behaviors.size(); i++)
		m_behaviors[i]->draw(this);
	Actor::draw();
}

void Agent::addForce(MathLibrary::Vector2 force)
{
	//add the force to the total force
	m_force = m_force + force;

	//if the total force magnitude is greater than the maxt force, set its magnitude to be the max Force
	if (m_force.getMagnitude() > getMaxForce())
		m_force = m_force.getNormalized() * getMaxForce();
}

void Agent::addBehavior(Behavior* behavior)
{
	if(behavior)
		m_behaviors.push_back(behavior);
}
