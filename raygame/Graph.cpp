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
	//Create a node pointer that points to the start node
	//Create a node pointer that points to the goal node
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);
	//Check if the start or the goal pointer is null
	if (!start || !goal)
		return std::vector<Node*>();
		//return an empty list
	//end if statement

	//Set the start nodes color to be green
	start->color = ColorToInt(GREEN);
	start->visited = true;
	//Create a node pointer that will be act as an iterator for the graph
	Node* currentNode = nullptr;
	//Create an open list
	//Create a closed list
	std::deque<Node*> open;
	std::deque<Node*> closed;
	//Add start to the open list
	open.push_back(start);
	//Loop while the open list is not empty
	while (!open.empty())
	{
		//Sort the items in the open list by the g score
		for (int i = 0; i < open.size(); i++)
		{
			for (int j = open.size() - 1; j < i; j--)
			{
				if (open[j]->gScore > open[j - 1]->gScore) {
					Node* temp = open[j];
					open[j] = open[j - 1];
					open[j - 1] = temp;
				}
			}
		}
		//Set the iterator to be the first item in the open list
		currentNode = open[0];
		//Check if the iterator is pointing to the goal node
		if (currentNode == goal)
		{
			std::vector<Node*> path;
			//Mark the goal as being found by changing its color
			currentNode->color = ColorToInt(YELLOW);
			currentNode->visited = true;
			//Return the new path found
			std::deque<Node*> flipPath;
			while (currentNode->Previous != nullptr) {
				flipPath.push_front(currentNode);
				for (int i = 0; i < currentNode->edges.size(); i++) 
				{
					if (currentNode->edges[i]->connectedNode1 == currentNode->Previous) {
						currentNode->edges[i]->color = ColorToInt(YELLOW);
					}
				}
				currentNode->color = ColorToInt(YELLOW);
				currentNode = currentNode->Previous;
			}
			for (int i = 0; i < flipPath.size(); i++)
			{
				path.push_back(flipPath[i]);
			}
			goal->color = ColorToInt(PURPLE);
			return path;
		}//end if statement

		//Pop the first item off the open list
		open.pop_front();
		//Add the first item to the closed list
		closed.push_back(currentNode);
		//Loop through all of the edges for the iterator
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* currentEdgeEnd = nullptr;
			//Check if the iterator is on the second end of the node
			if (currentNode == currentNode->edges[i]->connectedNode2)
				//Set the edge end pointer to be the first end of the node
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
			//Otherwise if the iterator is on the first end of the node...
			else
				//set the edge end pointer to be the second end of the node
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;
			// end if statement

			//Check if node at the end of the edge is in the closed list
			if (isInList(closed, currentNode))
			{
				//Create an int and set it to be the g score of the iterator plus the cost of the edge
				m_gScore = currentNode->gScore + currentNode->edges[i]->cost;
			}
			if (!isInList(open, currentEdgeEnd))
			{//Check if the node at the end of the edge is in the open list
				if (!currentEdgeEnd->visited) 
				{
					//Mark the node as visited by changing its color
					currentEdgeEnd->color = ColorToInt(RED);
					currentEdgeEnd->visited = true;
					//Set the nodes g score to be the g score calculated earlier
					currentEdgeEnd->gScore = m_gScore;
					//Set the nodes previous to be the iterator
					currentEdgeEnd->Previous = currentNode;
					//Add the node to the open list
					open.push_back(currentEdgeEnd);
				}
			}		
			else if(currentNode->gScore < currentEdgeEnd->gScore)
			{//Otherwise if the g score is less than the node at the end of the edge's g score...
				if (!currentEdgeEnd->visited)
				{
					//Mark the node as visited by changing its color
					currentEdgeEnd->color = ColorToInt(RED);
					currentEdgeEnd->visited = true;
					//Set the nodes g score to be the g score calculated earlier
					currentEdgeEnd->gScore = m_gScore;
					//Set its previous to be the current node
					currentEdgeEnd->Previous = currentNode;
				}
			}//end if statement
		}//end loop
	}//end loop
}

std::vector<Node*> Graph::aStar(int startX, int startY, int goalX, int goalY)
{
	//Create a node pointer that points to the start node
	//Create a node pointer that points to the goal node
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);
	//Check if the start or the goal pointer is null
	if (!start || !goal)
		return std::vector<Node*>();
	//return an empty list
//end if statement

//Set the start nodes color to be green
	start->color = ColorToInt(GREEN);
	start->visited = true;
	//Create a node pointer that will be act as an iterator for the graph
	Node* currentNode = nullptr;
	//Create an open list
	//Create a closed list
	std::deque<Node*> open;
	std::deque<Node*> closed;
	//Add start to the open list
	open.push_back(start);
	//Loop while the open list is not empty
	while (!open.empty())
	{
		//Sort the items in the open list by the g score
		for (int i = 0; i < open.size(); i++)
		{
			for (int j = open.size() - 1; j > i; j--)
			{
				if (open[j]->fScore < open[j - 1]->fScore) {
					Node* temp = open[j];
					open[j] = open[j - 1];
					open[j - 1] = temp;
				}
			}
		}
		//Set the iterator to be the first item in the open list
		currentNode = open[0];
		//Check if the iterator is pointing to the goal node
		if (currentNode == goal)
		{
			std::vector<Node*> path;
			//Mark the goal as being found by changing its color
			currentNode->color = ColorToInt(YELLOW);
			currentNode->visited = true;
			//Return the new path found
			std::deque<Node*> flipPath;
			while (currentNode->Previous != nullptr) {
				flipPath.push_front(currentNode);
				for (int i = 0; i < currentNode->edges.size(); i++)
				{
					if (currentNode->edges[i]->connectedNode1 == currentNode->Previous) {
						currentNode->edges[i]->color = ColorToInt(YELLOW);
					}
				}
				currentNode->color = ColorToInt(YELLOW);
				currentNode = currentNode->Previous;
			}
			for (int i = 0; i < flipPath.size(); i++)
			{
				path.push_back(flipPath[i]);
			}
			goal->color = ColorToInt(PURPLE);
			return path;
		}//end if statement

		//Pop the first item off the open list
		open.pop_front();
		//Add the first item to the closed list
		closed.push_back(currentNode);
		//Loop through all of the edges for the iterator
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* currentEdgeEnd = nullptr;
			//Check if the iterator is on the second end of the node
			if (currentNode == currentNode->edges[i]->connectedNode2)
				//Set the edge end pointer to be the first end of the node
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
			//Otherwise if the iterator is on the first end of the node...
			else
				//set the edge end pointer to be the second end of the node
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;
			// end if statement

			//Check if current node is in the closed list
			if (isInList(closed, currentNode))
			{
				//Create an int and set it to be the g score of the iterator plus the cost of the edge
				m_gScore = currentNode->gScore + currentNode->edges[i]->cost;
				//Create a float and set it to be the h score of the node at the end of the edge
				m_hScore = updateHScore(currentEdgeEnd,goal);
				//Create a float for the f score and set it to be the g score combined with the h score
				m_fScore = m_gScore + m_hScore;
				
			}
			if (!isInList(open, currentEdgeEnd))
			{//Check if the node at the end of the edge is not in the open list
				if (!isInList(closed,currentEdgeEnd)) {
					//Mark the node as visited by changing its color
					currentEdgeEnd->color = ColorToInt(RED);
					//Set the nodes g score to be the g score calculated earlier
					currentEdgeEnd->gScore = m_gScore;
					//Set the nodes h score to be the h score calculated earlier
					currentEdgeEnd->hScore = m_hScore;
					//Set its nodes f score to be the f score calculated earlier
					currentEdgeEnd->fScore = m_fScore;
					//Set the nodes previous to be the iterator
					currentEdgeEnd->Previous = currentNode;
					//Add the node to the open list
					open.push_back(currentEdgeEnd);
				}
			}
			else if (currentNode->fScore < currentEdgeEnd->fScore)
			{//Otherwise if the f score is less than the node at the end of the edge's f score...
					//Mark the node as visited by changing its color
				currentEdgeEnd->color = ColorToInt(RED);
				//Set the nodes g score to be the g score calculated earlier
				//Set its g score to be the g score calculated earlier
				currentEdgeEnd->gScore = m_gScore;
				//Set the nodes h score to be the h score calculated earlier
				currentEdgeEnd->hScore = m_hScore;
				//Set its f score to be the f score calculated earlier
				currentEdgeEnd->fScore = m_fScore;
				//Set its previous to be the current node
				//Set the nodes previous to be the iterator
				currentEdgeEnd->Previous = currentNode;
			}//end if statement
		}//end loop
	}//end loop
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

bool Graph::isInList(std::deque<Node*> list, Node* lookFor)
{
	for (int i = 0; i < list.size(); i++) {
		if (lookFor == list[i]) {
			return true;
		}
	}
	return false;
}

float Graph::updateHScore(Node* currentNode, Node* goalNode)
{
	int distanceX = abs(currentNode->graphPosition.x - goalNode->graphPosition.x);
	int distanceY = abs(currentNode->graphPosition.y - goalNode->graphPosition.y);
	if (distanceX > distanceY)
		return (1.42f * distanceY) + 1 * (distanceX - distanceY);
	else
		return (1.42f * distanceX) + 1 * (distanceY - distanceX);
}
