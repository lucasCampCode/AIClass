#pragma once
#include "ABDecision.h"
class HealthDecision :
    public ABDecision
{
public:
    using ABDecision::ABDecision;
    void makeDecision(Agent* agent, float deltaTime) override;
    bool checkCondition(Agent* agent, float deltaTime) override;
};

