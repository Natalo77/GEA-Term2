//=====================================================
//					Filename: AStar_Node.h
//=====================================================
#pragma once


//=====================================================
//					Include guards.
//=====================================================
#ifndef _NODE_GUARD
#define _NODE_GUARD


//=====================================================
//					Forward declarations.
//=====================================================
class AStar_Edge;
template class std::vector<AStar_Edge*>;


//=====================================================
//					Libraries.
//=====================================================
#include <OGRE/OgreVector2.h>


//=====================================================
//				Namespaces.
//=====================================================
using namespace Ogre;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    AStar_Node

  Summary:  A class to represent a traversable node in real space.

  Members:	AStar_Node* m_parent
				a pointer to the parent node of this node.
			float m_g
				a value to be used during AStarSearching storing the cumulative
				cost to this node.
			float m_h
				the heuristic value for this node.
			bool m_visited
				whether this node has been visited during a search or not.
			std::vector<AStar_Edge*>* m_neighbours
				A vector of edges directed towards the neighbour nodes of this node.
			Vector2 * m_position
				a 2D vector for the position of this node.

  Methods:  ====================== PUBLIC ======================
			AStar_Node()
				Default constructor of an AStar_Node
			~AStar()
				Default deconstructor of an AStar_Node

			AStar_Node(Vector2 * position)
				Constructor for an AStar_Node with an initial position).

			bool isEqual(AStar_Node* rhs)
				use to test equality between this node and the specified node.

			float getF()
				F = g + h.
			float getG()
				return this node's cumulative cost.

			void setG(float)
				set this node's cumulative cost.
			void SetH(float)
				set this node's heuristic cost.

			vector<AStar_Edge*>* getNeighbours()
				return this node's list of neighouring edges.

			bool isVisited()
				use to test this node's visited state.
			void setVisisted(bool)
				use to set this node's visited state.

			AStar_Node* getParent()
				use to return a pointer to this node's parent node.
			setParent(AStar_Node* newParent)
				Use to set this node's parent node.

			Vector2* getPosition()
				use to return a pointer to this node's 2D vector for position.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class AStar_Node
{
private:
	AStar_Node * m_parent;
	float m_g;
	float m_h;
	bool m_visited = false;
	std::vector<AStar_Edge*>* m_neighbours;
	Vector2 * m_position;

public:
	AStar_Node();
	~AStar_Node();

	AStar_Node(Vector2 * position);
	
	bool isEqual(AStar_Node* rhs);

	float getF();
	float getG();

	void setG(float);
	void setH(float);

	std::vector<AStar_Edge*>* getNeighbours();

	bool isVisited();
	void setVisited(bool);

	AStar_Node* getParent();
	void setParent(AStar_Node* newParent);

	Vector2* getPosition();
};

#endif

