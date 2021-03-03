#pragma once
#include "Agent.h"
class Enemy :
    public Agent
{
public:

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name="maxForce">The largest the magintude of the force vector can be</param>
    Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, Agent* agent,float maxSpeed = 1, float maxForce = 1);
    void update(float deltaTime) override;
    void setTarget(Agent* agent) { m_target = agent; }
private:
    Agent* m_target;
};

