//=====================================================
//					Filename: AStar_Edge.cpp
//=====================================================


//=====================================================
//				Defined libraries.
//=====================================================
#include "AStar_Edge.h"
#include "AStar_Node.h"

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   AStar_Edge

  Summary:  Default Constructor for the AStar_Edge class.

  Modifies: [none].

  Returns:  AStar_Edge
				the newly created AStar_Edge Object.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Edge::AStar_Edge()
{
	m_node = NULL;
	m_cost = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   ~AStar_Edge

  Summary:  Default DeConstructor for the AStar_Edge class.

  Modifies: [none].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Edge::~AStar_Edge()
{
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   AStar_Edge

  Summary:  Constructor for an edge object using a node and existing cost.

  Args:		AStar_Node* node
				a pointer to the node this edge leads towards.
			float cost
				the cost of this edge.

  Modifies: [m_node, m_cost].

  Returns:  AStar_Edge
				the newly created AStar_Edge Object.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Edge::AStar_Edge(AStar_Node* node, float cost)
{
	m_node = node;
	m_cost = cost;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   GetCost

  Summary:  Return the cost of this edge.

  Modifies: [none].

  Returns:  float
				the cost of this edge object.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
float AStar_Edge::GetCost()
{
	return m_cost;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   GetNode

  Summary:  Return the node this edge leads towards.

  Modifies: [none].

  Returns:  AStar_Node*
				a pointer to the node object this edge leads towards.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Node * AStar_Edge::GetNode()
{
	return m_node;
}
