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

		for (std::vector<AStar_Edge*>::iterator iter = currentNode->getNeighbours()->begin();	//Iterator at start of AStar_Edge list.
			iter != currentNode->getNeighbours()->end();										//Until iterator reaches end of list.
			iter++)																				//Increment Iterator by one.
		{
			if()
		}
		

	}


	return nullptr;
}

float AStar::ComputeHeuristic(AStar_Node * n1, AStar_Node * n2)
{
	return 0.0f;
}
