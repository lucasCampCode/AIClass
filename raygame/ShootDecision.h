#pragma once
#include "Decision.h"

class ShootDecision :
    public Decision
{
    void makeDecision(Agent* agent, float deltaTime) override;
private:
    float m_timer;
};

