

#include "TileManager.h"
#include "Tile.h"
#include "AStar_Node.h"
#include "AStar_Edge.h"


Ogre::Real TileManager::xOffset = 60;
Ogre::Real TileManager::zOffset = 50;


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


bool TileManager::Find(Tile *& result, Ogre::Vector3 &position)
{
	for (std::vector<Tile*>::iterator iter = tiles->begin();
		iter != tiles->end();
		iter++)
	{
		Tile* tile = *iter;
		if (position == tile->GetPosition())
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

AStar_Node * TileManager::GetGoalNode()
{
	return currentGoalTile->GetNode();
}

void TileManager::CycleTile(Tile *& tile)
{
	tile->CycleState();
	if (tile == currentGoalTile)
		currentGoalTile = NULL;
}


void TileManager::SetupEdges()
{
	//Each tile has 6 neighbours.
	/*
	
		   -1,-2   +1,-2
		-2,0	0,0		+2,0
		   -1,+2   +1,+2
	
	*/

	Tile* tile = NULL;
	for (std::vector<Tile*>::iterator iter = tiles->begin();
		iter != tiles->end();
		iter++)
	{
		tile = *iter;
		if (tile->GetState() != Tile::TILE_MOUNTAIN)
		{
			SetupEdges(tile);
		}
	}
}


void TileManager::TearDownEdges()
{
	Tile* tile = NULL;
	for (std::vector<Tile*>::iterator iter = tiles->begin();
		iter != tiles->end();
		iter++)
	{
		tile = *iter;
		TearDownEdges(tile);
	}
}


void TileManager::SetupEdges(Tile* tile)
{
	using V = Ogre::Vector3;
	int X = xOffset;
	int Z = zOffset;

	// Runs: TL, TR, R, BR, BL, L
	std::vector<Tile*> neighbours = { NULL, NULL, NULL, NULL, NULL, NULL };
	std::vector<Ogre::Vector3> offsets = { V(-X, 0, -2 * Z), V(X, 0, -2 * Z), V(2 * X, 0, 0), V(X, 0, 2 * Z), V(-X, 0, 2 * Z), V(-2 * X, 0, 0) };


	Ogre::Vector3 vec;
	for (int i = 0; i < 6; i++)
	{

		vec = Ogre::Vector3(tile->GetPosition() + offsets[i]);
		Find(neighbours[i], vec);
		if (neighbours[i] && neighbours[i]->GetState() != Tile::TILE_MOUNTAIN && neighbours[i]->GetState() != Tile::TILE_NA)
		{
			tile->GetNode()->AddNeighbour(neighbours[i]->GetNode(), 1.f);
		}
	}
}


void TileManager::TearDownEdges(Tile* tile)
{
	tile->GetNode()->getNeighbours()->clear();
}
