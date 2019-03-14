#pragma once

class AStar_Node;

class AStar_Edge
{
private:
	AStar_Node * m_node;
	float m_cost;

public:
	AStar_Edge();
	~AStar_Edge();

	AStar_Edge(AStar_Node* node, float cost);
};

