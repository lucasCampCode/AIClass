#pragma once
#include "SteeringBehavior.h"
class Actor;

class WanderingBehavior :
    public SteeringBehavior
{
public:
	WanderingBehavior();
	WanderingBehavior(float seekForce, float circleDistance = 1);

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;
	void draw(Agent* agent) override;
private:
	//the agent the behavior is seeking
	float m_seekForce;
	float m_circleDistance;
	MathLibrary::Vector2 m_startVector = { 1,0 };
	MathLibrary::Vector2 m_circle;
	MathLibrary::Vector2 m_point;
};

