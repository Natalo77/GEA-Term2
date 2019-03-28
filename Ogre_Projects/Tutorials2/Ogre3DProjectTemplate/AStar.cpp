#include "AStar.h"
#include "PriorityQueue.h"
#include "List.h"

AStar::AStar()
{
}

AStar::~AStar()
{
}

std::vector<AStar_Node>* AStar::AStarSearch(AStar_Node * start, AStar_Node * dest)
{
	PriorityQueue<AStar_Node*>* open = new PriorityQueue<AStar_Node*>();
	List<AStar_Node*>* closed = new List<AStar_Node*>();

	start->setVisited(true);
	start->setG(0.0f);
	start->setH(ComputeHeuristic(start, dest));

	open->push_back(start);

	while (!open->empty())
	{
		AStar_Node* currentNode = *(open->PopBack());
		if (currentNode->isEqual(dest))
			return ConstructPath(dest);

		for (std::vector<AStar_Edge*>::iterator iter = currentNode->getNeighbours()->begin();	//Iterator at start of AStar_Edge list.
			iter != currentNode->getNeighbours()->end();										//Until iterator reaches end of list.
			iter++)																				//Increment Iterator by one.
		{
			AStar_Edge* edge = *iter;
			float distance = edge->GetCost();
			AStar_Node* nextNode = edge->GetNode();
			if (!open->Contains(nextNode) && !closed->Contains(nextNode))
			{
				nextNode->setG(distance + currentNode->getG());
				nextNode->setH(ComputeHeuristic(nextNode, dest));
				nextNode->setParent(currentNode);
				open.
			}
		}
		

	}


	return nullptr;
}

float AStar::ComputeHeuristic(AStar_Node * n1, AStar_Node * n2)
{
	return 0.0f;
}

std::vector<AStar_Node>* AStar::ConstructPath(AStar_Node * dest)
{
	return &std::vector<AStar_Node>();
}
