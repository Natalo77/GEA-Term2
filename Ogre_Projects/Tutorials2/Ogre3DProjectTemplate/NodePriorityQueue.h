//=====================================================
//			Filename: NodePriorityQueue.h
//=====================================================
#pragma once


//=====================================================
//				Defined Libraries
//=====================================================
#include "PriorityQueue.h"


//=====================================================
//				Forward declarations.
//=====================================================
class AStar_Node;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    NodePriorityQueue

  Summary:  An extension of PriorityQueue to specialize the enqueue method
			to take into account node heuristic and cost.

  Methods:  ====================== PUBLIC ======================
			NodePriorityQueue()
				Default constructor for a NodePriorityQueue
			~NodePriorityQueue
				Defaul deconstructor for a NodePriorityQueue.

			void EnQueue(AStar_Node& element)
				Use to queue an AStarNode taking into account its heuristic and
				cost metrics.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class NodePriorityQueue : public PriorityQueue<AStar_Node*>
{
public:
	NodePriorityQueue();
	~NodePriorityQueue();

	void EnQueue(AStar_Node * element);
};

