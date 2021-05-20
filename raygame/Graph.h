#pragma once
#include "Actor.h"
#include <vector>
#include <deque>
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
    std::vector<Node*> aStar(int startX, int startY, int goalX, int goalY);
    Node* getNode(int xPos, int yPos);
    
private:
    void createGraph(int nodeSize, int nodeSpacing);
    bool isInList(std::deque<Node*> list, Node* lookFor);
    float updateHScore(Node* currentNode, Node* goalNode);
private:
    int m_width;
    int m_height;
    float m_gScore;
    float m_hScore;
    float m_fScore;
    std::vector<Node*> m_nodes;
};

