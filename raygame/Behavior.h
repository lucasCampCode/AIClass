#pragma once
class Agent;

class Behavior
{
public:
	virtual void update(Agent* agent, float deltaTime) = 0;
	virtual void draw(Agent* agent) {};
	bool getEnabled() { return m_enable; }
	void setEnabled(bool enable) { m_enable = enable; }
private:
	bool m_enable = true;
};