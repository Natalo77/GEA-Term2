#pragma once

class AStar_Node;
namespace Ogre {
	class SceneManager;
	class SceneNode;
}

#include <OgreMath.h>
#include <OgreString.h>
#include <OgreEntity.h>

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
	enum State { TILE_GRASS, TILE_MOUNTAIN, TILE_NA };

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

private:
	inline Ogre::String getMeshName(State state);
	inline Ogre::String getMaterialName(State state);

	void ChangeMesh(Ogre::String, Ogre::String);

private:
	State currentState;

	Ogre::SceneManager* scnMgr;

	Ogre::Entity* entity;

	Ogre::SceneNode* node;

	AStar_Node* m_AStarNode;
};

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
	}
}


inline Ogre::String Tile::getMaterialName(Tile::State state)
{
	switch (state)
	{
	case Tile::TILE_GRASS:
		return "Grass";
	case Tile::TILE_MOUNTAIN:
		return "Mountain";
	case Tile::TILE_NA:
		return "BlackAndWhite";
	}
}

