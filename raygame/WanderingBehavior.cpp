#include "WanderingBehavior.h"
#include "Agent.h"
#include "Actor.h"
#include <time.h>
#include "raylib.h"
WanderingBehavior::WanderingBehavior()
{
	srand(time(NULL));
	setForceScale(1);
	m_circleDistance = 1;
}

WanderingBehavior::WanderingBehavior(float seekForce, float circleDistance)
{
	srand(time(NULL));
	setForceScale(seekForce);
	m_circleDistance = circleDistance;
}

MathLibrary::Vector2 WanderingBehavior::calculateForce(Agent* agent)
{
	//grabs previous vector from wander and adds random jitter
	m_startVector = (m_startVector * getForceScale()) + MathLibrary::Vector2((rand()%3) - 1 , (rand() % 3) - 1);
	//normalize the vector
	m_startVector = MathLibrary::Vector2::normalize(m_startVector);
	//multiply the vector by force scale
	MathLibrary::Vector2 cirleDialate = m_startVector * getForceScale();
	//gets the distance for the cirlce to be
	MathLibrary::Vector2 circleDistance = agent->getForward() * m_circleDistance;
	//pushes the vector to create a possition to add the vector to move agent
	m_circle = agent->getWorldPosition() + circleDistance;
	//grabs the point from the distance of the circle and random point
	m_point = cirleDialate + m_circle;

	//finds the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_point - agent->getWorldPosition());
	//scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();
	//subtreact the desired velocity to the agents velocity
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();
	return steeringForce;
}

void WanderingBehavior::update(Agent* agent, float deltaTime)
{
	//if the agent isn't null, calculate a new force and aplly it to the agent
	if (agent)
		agent->addForce(calculateForce(agent));
}

void WanderingBehavior::draw(Agent* agent)
{
	DrawCircleLines(m_circle.x *32,m_circle.y*32,getForceScale()*32 , BLUE);
	DrawLine(m_circle.x * 32, m_circle.y * 32, m_point.x * 32, m_point.y * 32, RED);
}
