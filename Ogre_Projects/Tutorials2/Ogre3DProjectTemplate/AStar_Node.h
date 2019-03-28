#pragma once

#ifndef _NODE_GUARD
#define _NODE_GUARD

//#include <stdlib.h>
//#include <cstdlib>
#include <list>
#include <vector>

#include <OgreVector2.h>
#include <OgrePrerequisites.h>

#include "AStar_Edge.h"

using namespace Ogre;

class AStar_Node
{
private:
	AStar_Node * m_parent;
	float m_g;
	float m_h;
	bool m_visited = false;
	std::vector<AStar_Edge*>* m_neighbours; //Vector is a linked list with better search times
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

