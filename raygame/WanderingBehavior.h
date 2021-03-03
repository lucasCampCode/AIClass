#pragma once
#include "SteeringBehavior.h"
class Actor;

class WanderingBehavior :
    public SteeringBehavior
{
public:
	WanderingBehavior();
	WanderingBehavior(Actor* target, float seekForce = 1);

	void setTarget(Actor* target) { m_target = target; }
	Actor* getTarget() { return m_target; }

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;

private:
	//the agent the behavior is seeking
	Actor* m_target;
	float m_seekForce;
};

