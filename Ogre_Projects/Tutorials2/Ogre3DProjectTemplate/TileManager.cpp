//=====================================================
//				Filename: TileManager.cpp
//=====================================================


//=====================================================
//				Source Includes.
//=====================================================
#include "TileManager.h"
#include "Tile.h"
#include "AStar_Node.h"
#include "AStar_Edge.h"


//=====================================================
//				Static variable definition
//=====================================================
Ogre::Real TileManager::xOffset = 60;
Ogre::Real TileManager::zOffset = 50;


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		TileManager

Summary:	Default constructor for a TileManager

Modifies:	[mTiles, mCurrentGoalTile]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
TileManager::TileManager()
{
	mTiles = new std::vector<Tile*>();
	mCurrentGoalTile = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		~TileManager

Summary:	Default deconstructor for a TileManager

Modifies:	[mTiles, mCurrentGoalTile]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
TileManager::~TileManager()
{
	if(mTiles)
		delete [] mTiles;
	if (mCurrentGoalTile)
		delete mCurrentGoalTile;
	
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		Add

Summary:	Add a tile into consideration by the tileManager.

Args:		Tile & tileParent
				a reference to the tile to add into the tileManager.

Modifies:	[mTiles]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void TileManager::Add(Tile & tileParent)
{
	// Push the tile on to the tile list.
	mTiles->push_back(&tileParent);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		Find

Summary:	Find a tile based on its entity.

Args:		Tile *& result
				where to place the found tile.
			Entity & entity
				a reference of the entity to look for in the tiles list.

Returns:	bool
				was the tile found?
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
bool TileManager::Find(Tile *& result, Ogre::Entity & entity)
{
	// Iterate over the tiles list.
	for (std::vector<Tile*>::iterator iter = mTiles->begin();
		iter != mTiles->end();
		iter++)
	{
		// Dereference the iterator.
		Tile* tile = *iter;

		// If the entities match
		if (&entity == tile->GetEntity())
		{
			// Return it.
			result = tile;
			return true;
		}
	}


	return false;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		Find

Summary:	Find a tile based on its position.

Args:		Tile *& result
				where to place the found tile.
			Vector3 & position
				a reference of the position to look for in the tiles list.

Returns:	bool
				was the tile found?
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
bool TileManager::Find(Tile *& result, Ogre::Vector3 &position)
{
	// Iterate over the tiles list.
	for (std::vector<Tile*>::iterator iter = mTiles->begin();
		iter != mTiles->end();
		iter++)
	{
		// Dereference the iterator.
		Tile* tile = *iter;

		// If the positions match.
		if (position == tile->GetPosition())
		{
			// Return it.
			result = tile;
			return true;
		}
	}
	return false;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		Find

Summary:	Find a tile based on its node.

Args:		Tile *& result
				where to place the found tile.
			AStar_Node* node
				a pointer to the node to look for in the tiles list.

Returns:	bool
				was the tile found?
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
bool TileManager::Find(Tile *& result, AStar_Node * node)
{
	// Iterate over the list.
	for (std::vector<Tile*>::iterator iter = mTiles->begin();
		iter != mTiles->end();
		iter++)
	{
		// Dereference the iterator.
		Tile* tile = *iter;

		// If the nodes match
		if (node == tile->GetNode())
		{
			// Return it.
			result = tile;
			return true;
		}
	}
	return false;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		SetGoal

Summary:	Set the currentGoalTile

Args:		Tile *& goalTile
				a pointer reference to the tile to set as the new goal
				tile.

Modifies:	[mCurrentGoalTile]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void TileManager::SetGoal(Tile *& goalTile)
{
	// If there is a current Goal Tile, it's state is GOAL, and the goalTile is not the currentGoalTile.
	if (mCurrentGoalTile && mCurrentGoalTile->GetState() == Tile::TILE_GOAL && goalTile != mCurrentGoalTile)
		mCurrentGoalTile->CycleState(); // Cycle it off.

	// If the currentGoalTile is not the requestedGoalTile.
	if (mCurrentGoalTile != goalTile)
	{
		// Set the new goalTile.
		mCurrentGoalTile = goalTile;

		// Mark the tile as a goal.
		mCurrentGoalTile->SetGoal();
	}
		
	
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		GetGoalNode

Summary:	Get the ASTar_Node of the currentGoalTile.

Returns:	AStar_Node*
				A pointer to the AStarNode of the currentGoalTile.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Node * TileManager::GetGoalNode()
{
	return mCurrentGoalTile->GetNode();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		TilesReadyForTraversal

Summary:	Return whether or not the tiles have been set up properly
			by the user.

Returns:	bool
				Are the tiles ready for a traversal?
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
bool TileManager::TilesReadyForTraversal()
{
	// The only condition right now is that there is a goal tile.
	return mCurrentGoalTile != NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		CycleTile

Summary:	Cycle a tile through its states.

Args:		Tile *& tile
				the tile to cycle the state of.

Modifies:	[mCurrentGoalTile]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void TileManager::CycleTile(Tile *& tile)
{
	// Cycle the state of the tile.
	tile->CycleState();

	// If it was the goal tile, NULL it.
	if (tile == mCurrentGoalTile)
		mCurrentGoalTile = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		ResetTiles

Summary:	Reset all of the tiles under the tileManager.

Modifies:	[mTiles, mCurrentGoalTile]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void TileManager::ResetTiles()
{
	// Iterate over the tiles list.
	for (std::vector<Tile*>::iterator iter = mTiles->begin();
		iter != mTiles->end();
		iter++)
	{
		// Derefence the iterator.
		Tile* tile = *iter;

		//Reset the tile.
		tile->Reset();
	}

	// Null the currentGoalTile.
	mCurrentGoalTile = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		SetupEdges

Summary:	Calculate the edges for each of the tiles under consideration
			by the tileManager.

Modifies:	[mTiles]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void TileManager::SetupEdges()
{
	// Temp storage.
	Tile* tile = NULL;

	// iterate over the tiles list.
	for (std::vector<Tile*>::iterator iter = mTiles->begin();
		iter != mTiles->end();
		iter++)
	{
		// Dereference the iterator.
		tile = *iter;

		// If it's not a mountain
		if (tile->GetState() != Tile::TILE_MOUNTAIN)
		{
			// Setup the edges for it.
			SetupEdges(tile);
		}
	}
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		TearDownEdges

Summary:	tear the edges of each tile under consideration by the 
			tileManager.

Modifies:	[mTiles]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void TileManager::TearDownEdges()
{
	// Temp storage.
	Tile* tile = NULL;

	// Iterate over the tiles list.
	for (std::vector<Tile*>::iterator iter = mTiles->begin();
		iter != mTiles->end();
		iter++)
	{
		// Dereference the iterators.
		tile = *iter;

		// Tear down the edges for that tile.
		TearDownEdges(tile);
	}
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		SetNodeTraversed

Summary:	Set the Tile of the AStarNode to be traversed.

Args:		AStar_Node * node
				the node to set the Tile its connected to to be traversed.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void TileManager::SetNodeTraversed(AStar_Node * node)
{
	// Temp storage.
	Tile* tile = NULL;

	// If a tile was found with the node specified.
	if (Find(tile, node))
	{
		// If it's not a goalstate, set it to be traversed.
		if (tile->GetState() != Tile::TILE_GOAL)
			tile->SetTraversed();
	}
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		SetupEdges

Summary:	Setup the edges for an individual tile.

Args:		Tile * tile
				the tile to set up the edges for.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void TileManager::SetupEdges(Tile* tile)
{
	// Definitions to save space.
	using V = Ogre::Vector3;
	int X = xOffset;
	int Z = zOffset;

	//Each tile has 6 neighbours.
	/*

	   -1,-2   +1,-2
	-2,0	0,0		+2,0
	   -1,+2   +1,+2

	*/

	// Runs: TL, TR, R, BR, BL, L
	std::vector<Tile*> neighbours = { NULL, NULL, NULL, NULL, NULL, NULL };
	std::vector<Ogre::Vector3> offsets = { V(-X, 0, -2 * Z), V(X, 0, -2 * Z), V(2 * X, 0, 0), V(X, 0, 2 * Z), V(-X, 0, 2 * Z), V(-2 * X, 0, 0) };

	// Temp storage.
	Ogre::Vector3 vec;

	//For each possible tile.
	for (int i = 0; i < 6; i++)
	{
		// Calculate the supposed position of the tile.
		vec = Ogre::Vector3(tile->GetPosition() + offsets[i]);

		// Attempt to find a tile matching that position.
		Find(neighbours[i], vec);

		// IF a tile was found, AND it's not a mountain and it's not an NA
		if (neighbours[i] && neighbours[i]->GetState() != Tile::TILE_MOUNTAIN && neighbours[i]->GetState() != Tile::TILE_NA)
		{
			// Add it as a neghbour to the current tile, with a cost of 1.
			tile->GetNode()->AddNeighbour(neighbours[i]->GetNode(), 1.f);
		}
	}
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		TearDownEdges

Summary:	tear down the edges for an individual tile.

Args:		Tile * tile
				the tile to tear down the edges for.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void TileManager::TearDownEdges(Tile* tile)
{
	// Clear the neighbours vector of the tile's node.
	tile->GetNode()->getNeighbours()->clear();
}
