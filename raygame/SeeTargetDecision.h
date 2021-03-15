#pragma once
#include "ABDecision.h"
class SeeTargetDecision :
    public ABDecision
{
public:
    SeeTargetDecision(Decision* left,Decision* right,float maxAngle);
    void makeDecision(Agent* agent, float deltaTime) override;
    bool checkCondition(Agent* agent, float deltaTime) override;
private:
    float m_maxAngle;
};

