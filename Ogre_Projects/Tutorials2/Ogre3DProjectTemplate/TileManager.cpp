#include "TileManager.h"
#include "Tile.h"




TileManager::TileManager()
{
	tiles = new std::vector<Tile*>();
	currentGoalTile = NULL;
}


TileManager::~TileManager()
{
	if(tiles)
		delete [] tiles;
	if (currentGoalTile)
		delete currentGoalTile;
	
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


void TileManager::SetGoal(Tile *& goalTile)
{
	if (currentGoalTile && currentGoalTile->GetState() == Tile::TILE_GOAL && goalTile != currentGoalTile)
		currentGoalTile->CycleState();

	if (currentGoalTile != goalTile)
	{
		currentGoalTile = goalTile;
		currentGoalTile->SetGoal();
	}
		
	
}

void TileManager::CycleTile(Tile *& tile)
{
	tile->CycleState();
	if (tile == currentGoalTile)
		currentGoalTile = NULL;
}
