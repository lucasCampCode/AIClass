#pragma once
#include "Actor.h"
#include <vector>

class Node;
class Graph :
    public Actor
{
public:
    Graph(int width,int height, int nodeSize,int nodeSpacing);
    void draw() override;
    void update(float deltaTime)override;

    void BFS(int startX, int startY, int goalX, int goalY);
    std::vector<Node*> dijkstra(int startX, int startY, int goalX, int goalY);
    std::vector<Node*> dijkstraCustom(int startX, int startY, int goalX, int goalY);
    Node* getNode(int xPos, int yPos);
private:
    void createGraph(int nodeSize, int nodeSpacing);

private:
    int m_width;
    int m_height;
    std::vector<Node*> m_nodes;
};

