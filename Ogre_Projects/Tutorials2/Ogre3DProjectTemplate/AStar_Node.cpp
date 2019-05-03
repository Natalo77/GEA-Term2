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

  Modifies: [mNeighbours, mPosition, mParent].

  Returns:  AStar_Node
				the newly created AStar_Node object.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Node::AStar_Node()
{
	mNeighbours = new std::vector<AStar_Edge>();
	mPosition = new Vector2(0, 0);
	mParent = nullptr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   ~AStar_Node

  Summary:  The defauly deconstructor of an AStar_Node object.

  Modifies: [mParent, mNeighbours, mPosition].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Node::~AStar_Node()
{
	if(mParent)
		delete mParent;
	if(mNeighbours)
		delete[] mNeighbours;
	if(mPosition)
		delete mPosition;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   AStar_Node

  Summary:  Constructs an AStar_Node using a defined position.

  Args:     Vector2* position
				a pointer to an OgreVector2 to use as the position
				for this AStar_Node.

  Modifies: [mNeighbours, mPosition, mParent].

  Returns:  AStar_Node
				the newly created node object.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Node::AStar_Node(Vector2 * position)
{
	mNeighbours = new std::vector<AStar_Edge>();
	mPosition = position;
	mParent = NULL;
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
	return (mPosition->distance(*rhs->getPosition()) < 0.01f);
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
	return mG + mH;
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
	return this->mG;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   SetG

  Summary:  Set this node's cumulative cost.

  Args:     float g
				the value to assign to mG

  Modifies: [mG].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void AStar_Node::setG(float g)
{
	this->mG = g;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   setH

  Summary:  Set's this node's estimated cost (heuristic).

  Args:     float h
				the value to assign to mH

  Modifies: [mH].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void AStar_Node::setH(float h)
{
	this->mH = h;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   GetNeighbours

  Summary:  Return this node's list of neighbouring edges.

  Modifies: [none].

  Returns:  vector<AStar_Edge*>*
				a pointer to a vector containing all the neighbouring
				edges of this node.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
std::vector<AStar_Edge>* AStar_Node::getNeighbours()
{
	return mNeighbours;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   AddNeighbour

  Summary:  Creates and adds a new edge to this Node's neighbour vector.

  Args:		AStar_Node * node
				the node to add an edge leading towards.
			float cost
				the cost of the new edge.

  Modifies: [mNeighbours].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void AStar_Node::AddNeighbour(AStar_Node * node, float cost)
{
	// Create a new edge using the information given and push it onto the vector.
	AStar_Edge* edge = new AStar_Edge(node, cost);
	mNeighbours->push_back(*edge);
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
	return mVisited;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   setVisited

  Summary:  Set this node's visited state.

  Args:     bool visited
				the state to assign to mVisited.

  Modifies: [mVisited].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void AStar_Node::setVisited(bool visited)
{
	this->mVisited = visited;
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
	return mParent;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   setParent

  Summary:  Used to set the value of this node's parent for path construction.

  Args:     AStar_Node* newParent
				a pointer to the node to assign to mParent.

  Modifies: [mParent].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void AStar_Node::setParent(AStar_Node * newParent)
{
	mParent = newParent;
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
	return mPosition;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   ResetNode

  Summary:  Resets this node and all its members.

  Modifies: [mNeighbours, mPosition, mParent, mG, mH].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void AStar_Node::ResetNode()
{
	mParent = NULL;
	mG = INFINITY;
	mH = INFINITY;
	mVisited = false;
	mNeighbours->clear();
}


