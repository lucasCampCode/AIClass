#pragma once
#include "SteeringBehavior.h"
class Actor;

class WanderingBehavior :
    public SteeringBehavior
{
public:
	WanderingBehavior();
	WanderingBehavior(float seekForce);

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;

private:
	//the agent the behavior is seeking
	float m_seekForce;
};

