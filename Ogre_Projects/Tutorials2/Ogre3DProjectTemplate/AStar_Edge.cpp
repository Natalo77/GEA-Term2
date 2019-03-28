#include "AStar_Edge.h"
#include "AStar_Node.h"


AStar_Edge::AStar_Edge()
{
}


AStar_Edge::~AStar_Edge()
{
}


AStar_Edge::AStar_Edge(AStar_Node* node, float cost)
{
}

float AStar_Edge::GetCost()
{
	return m_cost;
}

AStar_Node * AStar_Edge::GetNode()
{
	return m_node;
}
