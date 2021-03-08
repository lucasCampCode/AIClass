#pragma once
#include "Actor.h"
#include "Behavior.h"
#include <vector>

class Agent : public Actor
{
public:
	Agent();
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name="maxForce">The largest the magintude of the force vector can be</param>
    Agent(float x, float y, float collisionRadius, char icon, float maxSpeed, float maxForce);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name="maxForce">The largest the magintude of the force vector can be</param>
    Agent(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed, float maxForce);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name="maxForce">The largest the magintude of the force vector can be</param>
    Agent(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float maxForce);

    void update(float deltaTime) override;
    void draw() override;
    //add the given force to the total force that is being applied by the agent;
    void addForce(MathLibrary::Vector2 force);

    void addBehavior(Behavior* behavior);

    float getMaxForce() { return m_maxForce; }
    void setMaxForce(float value) { m_maxForce = value; }
    
    template<typename BehaviorType>
    BehaviorType* getBehavior();

private:
	MathLibrary::Vector2 m_force;
	float m_maxForce;
	std::vector<Behavior*> m_behaviors;
};

template<typename BehaviorType>
inline BehaviorType* Agent::getBehavior()
{
    for (int i = 0; i < m_behaviors.size(); i++) 
    {
        BehaviorType* behavior = dynamic_cast<BehaviorType*>(m_behaviors[i]);

        if (behavior)
            return behavior;
    }

    return nullptr;
}
