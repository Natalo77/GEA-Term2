//=====================================================
//				Filename: AStar_Edge.h
//=====================================================
#pragma once

//=====================================================
//					Include Guards
//=====================================================
#ifndef _EDGE_GUARD
#define _EDGE_GUARD


//=====================================================
//				Forwards declarations.
//=====================================================
class AStar_Node;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    AStar_Edge

  Summary:  A class to represent an edge between two AStar_Nodes

  Members:	AStar_Node* m_node
				a pointer to the node this edge leads towards.
			float m_cost
				a value representing the cost/distance this edge takes
				to traverse.

  Methods:  ====================== PUBLIC ======================
			AStar_Edge()
				Default constructor of an AStar_Edge
			~AStar_Edge()
				Default deconstructor of an AStar_Edge

			AStar_Edge(AStar_Node* node, float cost)
				A constructor initializing the two members variables of
				this edge.

			float GetCost()
				return this edge's cost.
			AStar_Node* GetNode()
				return a pointer to the node this edge is directed towards.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class AStar_Edge
{
private:
	AStar_Node * m_node;
	float m_cost;

public:
	AStar_Edge();
	~AStar_Edge();

	AStar_Edge(AStar_Node* node, float cost);

	float GetCost();
	AStar_Node* GetNode();
};

#endif

