#pragma once
#include "Behavior.h"
#include <Vector2.h>
class SteeringBehavior : public Behavior 
{
public:
	virtual MathLibrary::Vector2 calculateForce(Agent* agent) = 0;
	virtual float getForceScale() { return m_forceScale; }
	virtual void setForceScale(float forceScale) { m_forceScale = forceScale; }
private:
	float m_forceScale = 1;
};