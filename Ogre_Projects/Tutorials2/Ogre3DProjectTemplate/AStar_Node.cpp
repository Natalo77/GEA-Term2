//=====================================================
//					Filename: AStar_Node.cpp
//=====================================================


//=====================================================
//					Defined Libraries.
//=====================================================
#include "AStar_Node.h"
#include "AStar_Edge.h"


//=====================================================
//					Libraries.
//=====================================================
#include <vector>


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   AStar_Node

  Summary:  The default constructor of an AStar_Node.
			Initializes this node at position 0,0

  Modifies: [m_neighbours, m_position, m_parent].

  Returns:  AStar_Node
				the newly created AStar_Node object.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Node::AStar_Node()
{
	m_neighbours = new std::vector<AStar_Edge*>();
	m_position = new Vector2(0, 0);
	m_parent = nullptr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   ~AStar_Node

  Summary:  The defauly deconstructor of an AStar_Node object.

  Modifies: [m_parent, m_neighbours, m_position].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Node::~AStar_Node()
{
	delete m_parent;
	delete m_neighbours;
	delete m_position;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   AStar_Node

  Summary:  Constructs an AStar_Node using a defined position.

  Args:     Vector2* position
				a pointer to an OgreVector2 to use as the position
				for this AStar_Node.

  Modifies: [m_neighbours, m_position, m_parent].

  Returns:  AStar_Node
				the newly created node object.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Node::AStar_Node(Vector2 * position)
{
	m_neighbours = new std::vector<AStar_Edge*>();
	m_position = position;
	m_parent = nullptr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   isEqual

  Summary:  Use to test equality between this node and 'rhs'

  Args:     AStar_Node * rhs
				the node to test this one for equality against.

  Modifies: [none].

  Returns:  bool
				are the two within 0.01f of eachother?
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
bool AStar_Node::isEqual(AStar_Node * rhs)
{
	return (m_position->distance(*rhs->getPosition()) < 0.01f);

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   GetF

  Summary:  Returns the cumulative cost + this node's heuristic value.

  Modifies: [none].

  Returns:  float
				the 'cost' of this node.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
float AStar_Node::getF()
{
	return m_g + m_h;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   GetG

  Summary:  Returns the cumulative cost of this node.

  Modifies: [none].

  Returns:  float
				the cumulative cost to this node thusfar in the search
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
float AStar_Node::getG()
{
	return this->m_g;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   SetG

  Summary:  Set this node's cumulative cost.

  Args:     float g
				the value to assign to m_g

  Modifies: [m_g].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void AStar_Node::setG(float g)
{
	this->m_g = g;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   setH

  Summary:  Set's this node's estimated cost (heuristic).

  Args:     float h
				the value to assign to m_h

  Modifies: [m_h].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void AStar_Node::setH(float h)
{
	this->m_h = h;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   GetNeighbours

  Summary:  Return this node's list of neighbouring edges.

  Modifies: [none].

  Returns:  vector<AStar_Edge*>*
				a pointer to a vector containing all the neighbouring
				edges of this node.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
std::vector<AStar_Edge*>* AStar_Node::getNeighbours()
{
	return m_neighbours;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   isVisited

  Summary:  check whether this node has been visited or not.

  Modifies: [none].

  Returns:  bool
				whether this node has been visited during a search or not.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
bool AStar_Node::isVisited()
{
	return m_visited;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   setVisited

  Summary:  Set this node's visited state.

  Args:     bool visited
				the state to assign to m_visited.

  Modifies: [m_visited].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void AStar_Node::setVisited(bool visited)
{
	this->m_visited = visited;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   getParent

  Summary:  Return the parent of this node related to path construction.

  Modifies: [none].

  Returns:  AStar_Node*
				a pointer to the parent node of this node in the current path.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Node * AStar_Node::getParent()
{
	return m_parent;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   setParent

  Summary:  Used to set the value of this node's parent for path construction.

  Args:     AStar_Node* newParent
				a pointer to the node to assign to m_parent.

  Modifies: [m_parent].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void AStar_Node::setParent(AStar_Node * newParent)
{
	m_parent = newParent;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   getPosition

  Summary:  Get the vector 2 position of this node.

  Modifies: [none].

  Returns:  OgreVector2
				a pointer to the vector 2 for the position of this node.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
Vector2 * AStar_Node::getPosition()
{
	return m_position;
}


