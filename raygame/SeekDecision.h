#pragma once
#include "Decision.h"
class SeekDecision :
    public Decision
{
    void makeDecision(Agent* agent, float deltaTime) override;
};

