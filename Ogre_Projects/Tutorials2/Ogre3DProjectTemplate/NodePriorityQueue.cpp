//=====================================================
//					Filename: NodePriorityQueue.cpp
//=====================================================


//=====================================================
//						Defined Headers.
//=====================================================
#include "NodePriorityQueue.h"
#include "AStar_Node.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   NodePriorityQueue

  Summary:  The default constructor for a NodePriorityQueue

  Modifies: [none].

  Returns:  NodePriorityQueue
				the newly created NodePriorityQueue object.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
NodePriorityQueue::NodePriorityQueue()
{
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   ~NodePriorityQueue

  Summary:  The default deconstructor for a NodePriorityQueue object.

  Modifies: [none].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
NodePriorityQueue::~NodePriorityQueue()
{
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   EnQueue

  Summary:  Queues the specified element into the Priority queue, basing
			its inserted position off the cumulative cost to traverse to it.

  Args:     AStar_Node & element
				a reference to the node to enqueue to the priority list.

  Modifies: [underlying data structure].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void NodePriorityQueue::EnQueue(AStar_Node * element)
{
	// Can just push back if its empty.
	if (this->empty())
	{
		this->push_back(element);
		return;
	}
	else
	{
		for (std::list<AStar_Node*>::iterator iter = this->begin();	//Iterator at start of AStar_Edge list.
			iter != this->end();										//Until iterator reaches end of list.
			iter++)
		{
			// Dereference the iterator,
			AStar_Node* node = *iter;

			// If the nodes priority is lesser than the examined node's
			if (element->getF() <= node->getF())
			{
				// Insert it ahead of that element and return.
				this->insert(iter, element);
				return;
			}
			else
				continue;
		}

		//If it was the highest cost element.
		this->push_back(element);
	}

	
}
