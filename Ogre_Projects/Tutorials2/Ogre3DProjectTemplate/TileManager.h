#pragma once


#ifndef _TILEMANAGER_H_
#define _TILEMANAGER_H_

#include <vector>

#include <OgreEntity.h>
#include <OgreMath.h>
#include "Tile.h"

class TileManager
{
public:
	TileManager();
	~TileManager();

	void Add(Tile &tileParent);

	bool Find(Tile *& result, Ogre::Entity &entity);
	bool Find(Tile *& result, Ogre::Vector3 &position);

	void SetGoal(Tile *& goalTile);
	AStar_Node* GetGoalNode();

	void CycleTile(Tile *& tile);

	void SetupEdges();
	void TearDownEdges();

public:
	static Ogre::Real xOffset;
	static Ogre::Real zOffset;

private:
	void SetupEdges(Tile * tile);
	void TearDownEdges(Tile* tile);

private:
	std::vector<Tile*>* tiles;

	Tile* currentGoalTile;
};




#endif

