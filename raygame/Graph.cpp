#include "Graph.h"
#include "Node.h"
#include "Edge.h"
Graph::Graph(int width, int height, int nodeSize, int nodeSpacing)
{
	m_width = width;
	m_height = height;

	createGraph(nodeSize, nodeSpacing);
}

void Graph::draw()
{
	for(int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i]->draw();
	}
}

void Graph::update(float deltaTime)
{
	Actor::update(deltaTime);
	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i]->update(deltaTime);
	}
}

void Graph::createGraph(int nodeSize, int nodeSpacing)
{
	float xPos = 0;
	float yPos = 0;

	//loops for the amount of nodes in the graph
	for (int i = 0; i < m_width * m_height; i++)
	{
		//create a new node with the current grapgh position and size
		Node* currentNode = new Node(xPos, yPos, nodeSize);
		//set the local offset for spacing
		currentNode->setLocalPosition({ xPos * nodeSpacing,yPos * nodeSpacing });
		//add the node as a child of the grid and update the list
		addChild(currentNode);
		m_nodes.push_back(currentNode);
		//connect the node to all nodes in range
		for (int j = 0; j < m_nodes.size(); j++) 
		{
			//find the displacement between teh current node being and the node being evaluated
			MathLibrary::Vector2 displacement = m_nodes[j]->graphPosition - currentNode->graphPosition;
			//check if the magnitude of the displacement id farther than the maximum
			if (displacement.getMagnitude() <= 1.42f && displacement.getMagnitude() > 0)
			{
				//create a new edge that connects the two nodes
				Edge* currentEdge = new Edge(m_nodes[j], currentNode);
				currentNode->edges.push_back(currentEdge);
				m_nodes[j]->edges.push_back(currentEdge);
			}
		}
		//increase the graph position on the x
		xPos++;
		//if the x position is greater than the width, reset it to 0 and increase the y
		if (xPos >= m_width)
		{
			xPos = 0;
			yPos++;
		}
	}
}
