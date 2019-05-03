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


//=====================================================
//					Libraries.
//=====================================================
#include <OGRE/OgreVector2.h>
#include <vector>


//=====================================================
//				Namespaces.
//=====================================================
using namespace Ogre;


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    AStar_Node

  Summary:  A class to represent a traversable node in real space.

  Members:	AStar_Node* mParent
				a pointer to the parent node of this node.
			float mG
				a value to be used during AStarSearching storing the cumulative
				cost to this node.
			float mH
				the heuristic value for this node.
			bool mVisited
				whether this node has been visited during a search or not.
			std::vector<AStar_Edge*>* mNeighbours
				A vector of edges directed towards the neighbour nodes of this node.
			Vector2 * mPosition
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
			void AddNeighbour(AStar_Node *, float cost)
				use to add a neighbour to this node.

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

			void ResetNode
				Use to reset this node and its neighbours.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class AStar_Node
{
private:
	AStar_Node * mParent;
	float mG = INFINITY;
	float mH = INFINITY;
	bool mVisited = false;
	std::vector<AStar_Edge>* mNeighbours;
	Vector2 * mPosition;

public:
	AStar_Node();
	~AStar_Node();

	AStar_Node(Vector2 * position);
	
	bool isEqual(AStar_Node* rhs);

	float getF();
	float getG();

	void setG(float);
	void setH(float);

	std::vector<AStar_Edge>* getNeighbours();
	void AddNeighbour(AStar_Node*, float cost);

	bool isVisited();
	void setVisited(bool);

	AStar_Node* getParent();
	void setParent(AStar_Node* newParent);

	Vector2* getPosition();

	void ResetNode();
};

#endif

