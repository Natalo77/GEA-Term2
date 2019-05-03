//=====================================================
//				Filename: TileManager.h
//=====================================================
#pragma once


//=====================================================
//				Include Guards.
//=====================================================
#ifndef _TILEMANAGER_H_
#define _TILEMANAGER_H_


//=====================================================
//				Library Includes.
//=====================================================
#include <vector>
#include <OgreEntity.h>
#include <OgreMath.h>


//=====================================================
//				Source Includes
//=====================================================
#include "Tile.h"


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:		TileManager

Summary:	A class to control and manage Tile objects in a gameSystem.

Methods:	==================== PUBLIC ====================
			TileManager
				default constructor for a tileManager.
			~TileManager
				default deconstructor for a tileManager.

			void Add(Tile &)
				add a tile into consideration by the tileManager.

			bool Find(Tile *&, Entity &)
				Find a tile based on its entity.
			bool Find(Tile *&, Vector3 &)
				Find a tile based on its position.
			bool Find(Tile *&, AStar_Node *)
				Find a tile based on its AStarNode.

			void SetGoal(Tile *&)
				Set this goal as the goalTile.
			AStar_Node* GetGoalNode
				Return the currentGoalNode.
			bool TilesReadyForTraversal
				Have the mTiles been set up properly for traversal by
				the user?

			void CycleTile(Tile *&)
				Cycle this tile through its states.
			void ResetTiles()
				reset every tile under the tileManagers consideration.

			void SetupEdges
				Calculate the edges within the tile domain for each Tile's
				AStarNode.
			void TearDownEdges
				Clean up all the edges within the tile domain for each
				Tile's AStarNode.

			void SetNodeTraversed(AStar_Node *)
				Set this node as traversed.

			==================== PRIVATE ====================
			void SetupEdges(Tile *)
				Setup the edges for this individual tile.
			void TearDownEdges(Tile *)
				Tear down the edges for this individual tile.

Members:	==================== PUBLIC ====================
			static Real xOffset
				the xOffset to use for the mTiles
			static Real zOffset
				the zOffset to use for the mTiles.

			==================== PRIVATE ====================
			vector<Tile*> mTiles
				the record of mTiles within the domain.
			Tile* mCurrentGoalTile
				the mCurrentGoalTile of the domain.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class TileManager
{
public:
	TileManager();
	~TileManager();

	void Add(Tile &tileParent);

	bool Find(Tile *& result, Ogre::Entity &entity);
	bool Find(Tile *& result, Ogre::Vector3 &position);
	bool Find(Tile *& result, AStar_Node * node);

	void SetGoal(Tile *& goalTile);
	AStar_Node* GetGoalNode();
	bool TilesReadyForTraversal();

	void CycleTile(Tile *& tile);
	void ResetTiles();

	void SetupEdges();
	void TearDownEdges();

	void SetNodeTraversed(AStar_Node* node);

private:
	void SetupEdges(Tile * tile);
	void TearDownEdges(Tile* tile);

public:
	static Ogre::Real xOffset;
	static Ogre::Real zOffset;

private:
	std::vector<Tile*>* mTiles;

	Tile* mCurrentGoalTile;
};




#endif

