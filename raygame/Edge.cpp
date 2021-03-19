#include "Edge.h"
#include "Node.h"
#include <raylib.h>

Edge::Edge(Node* node1, Node* node2): Actor(0,0,0,' ',0)
{
	connectedNode1 = node1;
	connectedNode2 = node2;
	cost = 1;
}

void Edge::draw()
{
	//draw a lineto represent each edge on the graph
	DrawLine(getWorldPosition().x * 32, getWorldPosition().y * 32,
		connectedNode2->getWorldPosition().x * 32, connectedNode2->getWorldPosition().y * 32, 
		WHITE);
}

void Edge::update(float deltaTime)
{
	Actor::update(deltaTime);
	//update the position to match the position of the first connected node
	setWorldPosition(connectedNode1->getWorldPosition());
}
