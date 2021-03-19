#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <deque>
#include <raylib.h>
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

void Graph::BFS(int startX, int startY, int goalX, int goalY)
{

	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);
	//if the start or the end is null return
	if (!start || !goal)
		return;
	//set the color to start and mark it as visited
	start->color = ColorToInt(GREEN);
	start->visited = true;
	//set the iterator to be the start node
	Node* currentNode = start;
	//create a queue to store the nodes
	std::deque<Node*> queue;
	//add the start node to the queue
	queue.push_back(start);

	//search for the goal while the queue isn't empty
	while (!queue.empty())
	{
		//set the current node to be the first item in the queue
		currentNode = queue[0];
		//remove the current node in question from queue
		queue.pop_front();
		//check if the iterator is the goal node
		if (currentNode == goal)
		{
			//set teh current node color to be yellow to mark it as found
			currentNode->color = ColorToInt(YELLOW);
			return;
		}
		//if the node wasn't the goal loop through it's edges to get it's neighbours
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			//create a point to store the node at the other end of the edge
			Node* currentEdgeEnd = nullptr;
			
			//set the pointer to be the opposite end of the edge
			if (currentNode == currentNode->edges[i]->connectedNode2)
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
			else
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;

			//if the node at the opposite end hassn't been visited mark it as visited and add it to the queue
			if (!currentEdgeEnd->visited)
			{
				currentEdgeEnd->color = ColorToInt(RED);
				currentEdgeEnd->visited = true;
				queue.push_back(currentEdgeEnd);
			}
		}
	}
}

std::vector<Node*> Graph::dijkstra(int startX, int startY, int goalX, int goalY)
{

	return std::vector<Node*>();
}



Node* Graph::getNode(int xPos, int yPos)
{
	if(xPos < 0 || xPos > m_width || yPos < 0 || yPos > m_height)
		return nullptr;

	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes[i]->graphPosition == MathLibrary::Vector2(xPos, yPos))
			return m_nodes[i];
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
