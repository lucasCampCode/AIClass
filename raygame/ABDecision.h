#pragma once
#include "Decision.h"
class ABDecision :
    public Decision
{
public:
    ABDecision(Decision* left,Decision* right);

    void makeDecision(Agent* agent, float deltaTime) override;
    virtual bool checkCondition(Agent* agent, float deltaTime);

    bool getChoice() { return m_choice; }
    void setChoice(bool choice) { m_choice = choice; }

private:
    bool m_choice;
    Decision* m_left;
    Decision* m_right;
};

