#pragma once

#ifndef _EDGE_GUARD
#define _EDGE_GUARD

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

	float GetCost();

	AStar_Node* GetNode();
};

#endif

