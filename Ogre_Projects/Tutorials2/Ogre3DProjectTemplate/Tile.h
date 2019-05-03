#pragma once

class AStar_Node;
namespace Ogre {
	class SceneManager;
	class SceneNode;
}

#include <OgreMath.h>
#include <OgreString.h>
#include <OgreEntity.h>

#include <vector>

struct EntityComparable
{
	bool operator() (const Ogre::Entity& lhs, const Ogre::Entity& rhs) const
	{
		return lhs.getName() < rhs.getName();
	}
};

class Tile
{
public:
	enum State { TILE_GRASS, TILE_MOUNTAIN, TILE_GOAL, TILE_TRAVERSED, TILE_NA };

	Tile();
	~Tile();
	Tile(
		Ogre::SceneManager &scnMgr, 
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
	State currentState;

	Ogre::SceneManager* scnMgr;

	Ogre::Entity* entity;

	Ogre::SceneNode* node;

	AStar_Node* m_AStarNode;
};


inline void Tile::UpdateModel()
{
	Ogre::String newMeshString = getMeshName(currentState);
	std::vector<Ogre::String> newMaterialStrings = getMaterialName(currentState);

	ChangeMesh(newMeshString, newMaterialStrings);
}


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

