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

	m_startVector = (m_startVector * getForceScale()) + MathLibrary::Vector2((rand()%3) - 1 , (rand() % 3) - 1);
	m_startVector = MathLibrary::Vector2::normalize(m_startVector);
	MathLibrary::Vector2 cirleDialate = m_startVector * getForceScale();
	MathLibrary::Vector2 circleDistance = agent->getForward() * m_circleDistance;
	m_circle = agent->getWorldPosition() + circleDistance;
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
	DrawCircleLines(m_circle.x *32,m_circle.y*32,m_seekForce*32 , BLUE);
	DrawLine(m_circle.x * 32, m_circle.y * 32, m_point.x * 32, m_point.y * 32, RED);
}
