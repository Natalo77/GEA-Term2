#include "AStar.h"

AStar::AStar()
{
}

AStar::~AStar()
{
}

std::vector<AStar_Node>* AStar::AStarSearch(AStar_Node * start, AStar_Node * dest)
{
	std::priority_queue<AStar_Node*>* open = new std::priority_queue<AStar_Node*>();
	std::vector<AStar_Node*>* closed = new std::vector<AStar_Node*>();

	start->setVisited(true);
	start->setG(0.0f);
	start->setH(ComputeHeuristic(start, dest));

	open->push(start);

	while (!open->empty)
	{
		AStar_Node* currentNode = open->top;
		//...
		for (uint i = 0; i < currentNode->getNeighbours()->size; i++)
		{

		}
		

	}


	return nullptr;
}

float AStar::ComputeHeuristic(AStar_Node * n1, AStar_Node * n2)
{
	return 0.0f;
}
