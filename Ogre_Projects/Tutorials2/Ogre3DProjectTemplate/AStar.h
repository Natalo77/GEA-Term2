#pragma once

#include "AStar_Edge.h"
#include "AStar_Node.h"

#include <queue>
#include <vector>

class AStar
{
private:

public:
	AStar();
	~AStar();

	static std::vector<AStar_Node>* AStarSearch(AStar_Node* start, AStar_Node* dest);

	static float ComputeHeuristic(AStar_Node* n1, AStar_Node* n2);
};

