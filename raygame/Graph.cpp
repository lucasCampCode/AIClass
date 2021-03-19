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
		//return an empty list
	if (!start || !goal)
		return std::vector<Node*>();
	//end if statement

	//Set the start nodes color to be green
	start->color = ColorToInt(GREEN);

	//Create a node pointer that will be act as an iterator for the graph
	Node* currentNode = nullptr;
	//Create an open list
	std::deque<Node*> open;
	//Create a closed list
	std::deque<Node*> closed;
	//Add start to the open list
	open.push_back(start);
	//Loop while the open list is not empty
	while (!open.empty()) {
		//Sort the items in the open list by the g score
		if (open.size() > 1) {
			for (int i = 0; i < open.size(); i++)
			{
				int k = 0;
				for (int j = open.size(); i < j; j--)
				{
					k = j - 1;
					if (open[j]->gScore < open[k]->gScore)
					{
						Node* temp = open[j];
						open[j] = open[k];
						open[k] = temp;
					}
				}
			}
		}
		//Set the iterator to be the first item in the open list
		currentNode = open[0];
		//Check if the iterator is pointing to the goal node
		if (currentNode == goal) {
			std::vector<Node*> foundPath;
			//Mark the goal as being found by changing its color
			currentNode->color = ColorToInt(GREEN);
			currentNode->visited = true;
			//Return the new path found
			while (currentNode->Previous != nullptr) {
				foundPath.push_back(currentNode);
				currentNode = currentNode->Previous;
			}
			for (int i = 0; i < foundPath.size(); i++)
			{
				if (i == 0)
					foundPath.insert(foundPath.begin(), foundPath[foundPath.size()]);
				else
					foundPath.insert(foundPath.begin()++, foundPath[foundPath.size()]);
				foundPath.pop_back();
			}
			return foundPath;
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
			for (int j = 0; j < closed.size(); j++) {
				if (currentEdgeEnd == closed[j]) {
					//Create an int and set it to be the g score of the iterator plus the cost of the edge
					float score = currentNode->gScore + currentNode->edges[i]->cost;

					//Check if the node at the end ofthe edge is in the open list
					for (int k = 0; k < open.size(); k++)
					{
						if (currentEdgeEnd == open[k])
						{
							//Mark the node as visited by changing its color
							currentEdgeEnd->color = ColorToInt(RED);
							currentEdgeEnd->visited = true;
							//Set the nodes g score to be the g score calculated earlier
							currentEdgeEnd->gScore = score;
							//Set the nodes previous to be the iterator
							//Add the node to the open list
							open.push_back(currentEdgeEnd);
						}
					}//Otherwise if the g score is less than the node at the end of the edge's g score...
					if (currentNode->gScore < currentEdgeEnd->gScore)
					{
						//Mark the node as visited by changing its color
						currentEdgeEnd->color = ColorToInt(RED);
						currentEdgeEnd->visited = true;
						//Set its g score to be the g score calculated earlier
						currentEdgeEnd->gScore = score;
						//Set its previous to be the current node
						currentEdgeEnd->Previous = currentNode;
					}
				}
			}//end if statement
		}//end loop
	}//end loop
}

std::vector<Node*> Graph::dijkstraCustom(int startX, int startY, int goalX, int goalY)
{
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);
	std::deque<Node*> foundPath;
	//if the start or the end is null return
	if (!start || !goal)
		return std::vector<Node*>();
	//set the color to start and mark it as visited
	start->color = ColorToInt(GREEN);
	start->visited = true;
	//set the iterator to be the start node
	Node* currentNode = nullptr;
	//create a queue to store the nodes
	std::deque<Node*> open;
	std::deque<Node*> closed;
	//add the start node to the queue
	open.push_back(start);

	//search for the goal while the queue isn't empty
	while (!open.empty())
	{
		//set the current node to be the first item in the queue
		currentNode = open[0];
		//remove the current node in question from queue
		open.pop_front();
		//check if the iterator is the goal node
		if (currentNode == goal)
		{
			std::vector<Node*> path;
			//set the current node color to be green to mark it as found
			currentNode->color = ColorToInt(GREEN);
			while (currentNode->Previous != nullptr)
			{
				foundPath.push_front(currentNode);
				currentNode = currentNode->Previous;
			}
			for (int i = 0; i < foundPath.size(); i++)
			{
				path.push_back(foundPath[i]);
			}
			return path;
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
				open.push_back(currentEdgeEnd);
			}
		}
	}

	//Create a node pointer that will be act as an iterator for the graph
	//Create an open list
	//Create a closed list

	//Add start to the open list

	//Loop while the open list is not empty

		//Sort the items in the open list by the g score

		//Set the iterator to be the first item in the open list

		//Check if the iterator is pointing to the goal node

			//Mark the goal as being found by changing its color
			//Return the new path found

		//end if statement

		//Pop the first item off the open list
		//Add the first item to the closed list

		//Loop through all of the edges for the iterator

			//Create a node pointer to store the other end of the edge

			//Check if the iterator is on the second end of the node
				//Set the edge end pointer to be the first end of the node
			//Otherwise if the iterator is on the first end of the node...
				//set the edge end pointer to be the second end of the node
			// end if statement

			//Check if node at the end of the edge is in the closed list

				//Create an int and set it to be the g score of the iterator plus the cost of the edge


				//Check if the node at the end ofthe edge is in the open list

					//Mark the node as visited by changing its color
					//Set the nodes g score to be the g score calculated earlier
					//Set the nodes previous to be the iterator
					//Add the node to the open list

				//Otherwise if the g score is less than the node at the end of the edge's g score...

					//Mark the node as visited by changing its color
					//Set its g score to be the g score calculated earlier
					//Set its previous to be the current node

				//end if statement
		//end loop
	//end loop
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
