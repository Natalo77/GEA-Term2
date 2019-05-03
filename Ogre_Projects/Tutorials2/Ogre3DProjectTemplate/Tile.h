//=====================================================
//					Filename: Tile.h
//=====================================================
#pragma once


//=====================================================
//				Forward Declarations.
//=====================================================
class AStar_Node;
namespace Ogre {
	class SceneManager;
	class SceneNode;
}


//=====================================================
//				Library Includes.
//=====================================================
#include <OgreMath.h>
#include <OgreString.h>
#include <OgreEntity.h>
#include <vector>


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:		Tile

Summary:	A class to represent and provide methods of altering and
			adjusting a singular tile.

Enums:		State: TILE_
				GRASS, MOUNTAIN, GOAL, TRAVERSED, NA
				an Enum to describe various states a tile can be in.

Methods:	==================== PUBLIC ====================
			TIle
				The default constructor of a Tile.
			~Tile
				the default deconstructor of a Tile.
			Tile(SceneManager &, String &, String, Vector3 &, Quaternion &)
				The preferred constructor of a Tile.

			Entity* GetEntity
				Return a pointer to this tile's mEntity
			AStar_Node* GetNode
				return a pointer to this tile's AStar_Node

			State CycleState
				Cycle this tile to the next logical state.
			void Reset()
				Reset this tile and its current state.

			void SetGoal()
				Set this tile as a goal tile.
			State GetState()
				get this tile's current state.

			void SetTraversed()
				Mark this tile as traversed.

			Vector3 GetPosition
				Get this tile's position in world space.

			==================== PRIVATE ====================
			inline void UpdateModel()
				Use the data members stored to update this tile's mEntity

			inline String GetMeshName(State state)
				Return a string for the model to be used for the state.
			inline std::vector<String> GetMaterialName(State state)
				Return a vector of strings for the material names for this state.

			void ChangeMesh(String &, vector<String>&)
				Use the data to update the mesh of the mEntity of this tile.

Members:	==================== PRIVATE ====================
			State mCurrentState
				the mCurrentState of this tile.
			SceneManager* g_ScnMgr
				a pointer to the sceneManager used to create this tile.
			Entity* mEntity
				a pointer to the mEntity of this tile.
			SceneNode* mSceneNode
				a pointer to the sceneNode used for the mEntity of this tile.
			AStar_Node* mAStarNode
				a pointer to the AStar_node attached to this Tile.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Tile
{
public:
	enum State { TILE_GRASS, TILE_MOUNTAIN, TILE_GOAL, TILE_TRAVERSED, TILE_NA };

	Tile();
	~Tile();
	Tile(
		Ogre::SceneManager &g_ScnMgr, 
		Ogre::String &name, 
		const Ogre::String materialName,
		const Ogre::Vector3 &position,
		const Ogre::Quaternion &rotation);

	Ogre::Entity* GetEntity();
	AStar_Node* GetNode();

	State CycleState();
	void Reset();

	void SetGoal();
	State GetState();

	void SetTraversed();

	Ogre::Vector3 GetPosition();

private:
	inline void UpdateModel();

	inline Ogre::String getMeshName(State state);
	inline std::vector<Ogre::String> getMaterialName(State state);

	void ChangeMesh(Ogre::String&, std::vector<Ogre::String>&);

private:
	State mCurrentState;

	Ogre::SceneManager* g_ScnMgr;

	Ogre::Entity* mEntity;

	Ogre::SceneNode* mSceneNode;

	AStar_Node* mAStarNode;
};


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:   UpdateModel

Summary:  Update the model ued by the Ogre rendering representation.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
inline void Tile::UpdateModel()
{
	// Get the mesh name for the currentState.
	Ogre::String newMeshString = getMeshName(mCurrentState);

	// Get the material names for the current state.
	std::vector<Ogre::String> newMaterialStrings = getMaterialName(mCurrentState);

	//Change the mesh using the obtained strings.
	ChangeMesh(newMeshString, newMaterialStrings);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		operator ++

Summary:	Provide an override of the ++ operator so the tiles can
			be cycled through.

Args:		State &
				the state enum to be incremented.
			int
				designates postfix increment operator.

Returns:	State
				the incremented State
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
inline Tile::State operator ++(Tile::State& state, int)
{
	switch (state)
	{
	case Tile::TILE_GRASS:
		state = Tile::TILE_MOUNTAIN;
		return state;
	case Tile::TILE_MOUNTAIN:
		state = Tile::TILE_GRASS;
		return state;
	case Tile::TILE_NA:
		return state;
	case Tile::TILE_GOAL:
		state = Tile::TILE_GRASS;
		return state;
	case Tile::TILE_TRAVERSED:
		return state;
	}
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		GetMeshName

Summary:	Return the correct mesh name for each state.

Args:		State 
				the state to be looked up.

Returns:	String
				The correct mesh name.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
inline Ogre::String Tile::getMeshName(Tile::State state)
{
	switch (state)
	{
	case Tile::TILE_GRASS:
		return "GrassTile.mesh";
	case Tile::TILE_MOUNTAIN:
		return "MountainTile.mesh";
	case Tile::TILE_NA:
		return "GrassTile.mesh";
	case Tile::TILE_GOAL:
		return "GoalTile.mesh";
	case Tile::TILE_TRAVERSED:
		return "GrassTile.mesh";
	}
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		GetMaterialName

Summary:	Return a vector of material names for the state.

Args:		State 
				the state to be queried.

Returns:	vector<String>
				A vector containing the material names used for the mesh.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
inline std::vector<Ogre::String> Tile::getMaterialName(Tile::State state)
{
	std::vector<Ogre::String> temp;

	switch (state)
	{
	case Tile::TILE_GRASS:
		temp.push_back("Grass");
		break;
	case Tile::TILE_MOUNTAIN:
		temp.push_back("Mountain");
		break;
	case Tile::TILE_NA:
		temp.push_back("BlackAndWhite");
		break;
	case Tile::TILE_GOAL:
		temp.push_back("StoneGoal");
		temp.push_back("SoilGoal");
		break;
	case Tile::TILE_TRAVERSED:
		temp.push_back("VisitedTile");
		break;
	}

	return temp;
}

