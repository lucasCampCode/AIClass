#pragma once
class Agent;

class Behavior
{
public:
	virtual void update(Agent* agent, float deltaTime) = 0;
};