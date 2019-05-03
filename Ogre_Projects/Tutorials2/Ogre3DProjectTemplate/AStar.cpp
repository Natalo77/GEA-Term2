//=====================================================
//				Filename: AStar.cpp
//=====================================================


//=====================================================
//					Defined Libraries
//=====================================================

#include "AStar_Edge.h"
#include "AStar_Node.h"
#include "NodePriorityQueue.h"
#include "AList.h"
#include "AStar.h"





/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   AStar

  Summary:  Default Constructor for the AStar class.

  Modifies: [none].

  Returns:  AStar
				the newly created AStar Object.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar::AStar()
{
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   ~AStar

  Summary:  Default Deconstructor for the AStar class.

  Modifies: [none].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar::~AStar()
{
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   AStarSearch

  Summary:  Searches for and returns the shortest valid path between
			two interconnected nodes: start and dest.

  Args:     AStar_Node* start
				the node from which to construct the path.
			AStar_Node* dest
				the node to construct the path to.

  Modifies: [none].

  Returns:  AList<AStar_Node>*
				A pointer to a AList containing a path from start to dest.
				nullptr if no path could be found.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AList<AStar_Node*>* AStar::AStarSearch(AStar_Node * start, AStar_Node * dest)
{
	// Initialize an open and closed list.
	NodePriorityQueue* open = new NodePriorityQueue();
	AList<AStar_Node*>* closed = new AList<AStar_Node*>();

	// Visit the first node and compute the heuristics for it.
	start->setVisited(true);
	start->setG(0.0f);
	start->setH(ComputeHeuristic(start, dest));

	// Add the starting node to the Priority queue.
	open->push_back(start);

	// While there are still elements to be visited.
	while (!open->empty())
	{
		// Get the highest priority element.
		AStar_Node* currentNode = open->DeQueue();

		// If the dest node has been found then return a path to that destination node.
		if (currentNode->isEqual(dest))
			return ConstructPath(dest);

		// Iterate over the currentNode's neighbours.
		for (std::vector<AStar_Edge>::iterator iter = currentNode->getNeighbours()->begin();	//Iterator at start of AStar_Edge list.
			iter != currentNode->getNeighbours()->end();										//Until iterator reaches end of list.
			iter++)																				//Increment Iterator by one.
		{
			// Dereference the iterator.
			AStar_Edge edge = *iter;

			// Get the cost of the edge.
			float distance = edge.GetCost();

			// Get a pointer to the edge's leading node.
			AStar_Node* nextNode = edge.GetNode();

			// If the nextNode has not been visited.
			if (!open->Contains(nextNode) && !closed->Contains(nextNode))
			{
				// Calculate the cost and heuristic for this node to the destination node.
				nextNode->setG(distance + currentNode->getG());
				nextNode->setH(ComputeHeuristic(nextNode, dest));

				// Set the parent of the nextNode as the currentNode. 
				nextNode->setParent(currentNode);

				// Then enqueue the nextNode to be visited.
				open->EnQueue(nextNode);
			}
			// if it has been visited and the cumulative distance + the edge cost is less than the nextNode's cumulative distance
			// aka. the path is viable over an existing one.
			else if (distance + currentNode->getG() < nextNode->getG())
			{
				// Set the cost and compute the heuristic of the nextNode to the destination.
				nextNode->setG(distance + currentNode->getG());
				nextNode->setH(ComputeHeuristic(nextNode, dest));

				// remove the nextNode from the open and closed.
				open->remove(nextNode);
				closed->Remove(nextNode);

				// then requeue it for the new path calculations
				open->EnQueue(nextNode);
			}
		}

		// finally add the current node to the closed list when all is done.
		closed->push_back(currentNode);
	}

	//If no path was found, return nullptr.
	return nullptr;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   ComputeHeuristic

  Summary:  Calculates and returns the heuristic(estimated cost) from n1
			to n2.

  Args:     AStar_Node* n1
				the 'from' node.
			AStar_Node* n2
				the 'to' node.

  Modifies: [none].

  Returns:  float
				the estimated distance between the two.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
float AStar::ComputeHeuristic(AStar_Node * n1, AStar_Node * n2)
{
	// This implementation simply returns the square of the euclidean distance
	// between the two nodes. Square is used as comparison is the only function here.
	return n1->getPosition()->distance(*n2->getPosition());
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   ConstructPath

  Summary:  Uses the successive calculated parents of dest to construct
			a list of AStar_Nodes representing a path to the destination node.

  Args:     AStar_Node* dest
				the destination node.

  Modifies: [none].

  Returns:  AList<AStar_Node>
				a list of nodes in reverse order (dest at the front) representing
				the path to dest from the final node in the list.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AList<AStar_Node*>* AStar::ConstructPath(AStar_Node * dest)
{
	// Create a list to store the path in and add the dest node.
	AList<AStar_Node*>* path = new AList<AStar_Node*>();
	AStar_Node* current = dest;
	path->push_back(current);

	// While there is still a parent to the current node.
	while ( nullptr != current->getParent())
	{
		// Update the current node with its parent.
		current = current->getParent();

		// and push it back onto the path list.
		path->push_back(current);
	}

	// Return the calculated path.
	return path;
}
