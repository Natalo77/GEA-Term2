#include "TileManager.h"




TileManager::TileManager()
{
	tiles = new std::vector<Tile*>();
}


TileManager::~TileManager()
{
	delete [] tiles;
}


void TileManager::Add(Tile & tileParent)
{
	tiles->push_back(&tileParent);
}


bool TileManager::Find(Tile *& result, Ogre::Entity & entity)
{
	for (std::vector<Tile*>::iterator iter = tiles->begin();
		iter != tiles->end();
		iter++)
	{
		Tile* tile = *iter;
		if (&entity == tile->GetEntity())
		{
			result = tile;
			return true;
		}
	}


	return false;
}
