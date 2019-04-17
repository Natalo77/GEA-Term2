//=====================================================
//					Filename: AStar.h
//=====================================================
#pragma once

//=====================================================
//					Include Guards.
//=====================================================
#ifndef _ASTAR_GUARD
#define _ASTAR_GUARD


//=====================================================
//				Forward Declarations
//=====================================================
class AStar_Edge;
class AStar_Node;
template class List<AStar_Node>;


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    AStar

  Summary:  A utility class providing static methods to be used by an 
			'agent' to intelligently construct a path between two nodes.

  Methods:  ====================== PUBLIC ======================
			AStar()
				Default constructor of AStar
			~AStar()
				Default deconstructor of AStar

			static List<AStar_Node>* AStarSearch(AStar_Node* start, AStar_Node* dest)
				Use to return the shortest path of nodes from start to dest

			====================== PRIVATE ======================
			static float ComputeHeuristic(AStar_Node* n1, AStar_Node* n2)
				Used by AStarSearch to compute a heuristic between the two specified nodes.

			static List<AStar_Node>* ConstructPath(AStar_Node* dest)
				Used by AStarSearch to construct the final path to be returned.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class AStar
{
private:

public:
	AStar();
	~AStar();

	static List<AStar_Node>* AStarSearch(AStar_Node* start, AStar_Node* dest);

private:
	static float ComputeHeuristic(AStar_Node* n1, AStar_Node* n2);

	static List<AStar_Node>* ConstructPath(AStar_Node* dest);
};

#endif

