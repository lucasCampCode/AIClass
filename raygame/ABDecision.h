#pragma once
#include "Decision.h"
class ABDecision :
    public Decision
{
public:
    void makeDecision(Agent* agent, float deltaTime) override;
private:
    bool m_choice;
    Decision* m_left;
    Decision* m_right;
};

