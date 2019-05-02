#pragma once

#include <vector>

#include <OgreEntity.h>
#include "Tile.h"

class TileManager
{
public:
	TileManager();
	~TileManager();

	void Add(Tile &tileParent);

	bool Find(Tile *& result, Ogre::Entity &entity);

private:
	std::vector<Tile*>* tiles;
};
