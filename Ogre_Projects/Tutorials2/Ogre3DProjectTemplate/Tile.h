#pragma once

namespace Ogre {
	class SceneManager;
}

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
	Tile();
	~Tile();
	Tile(Ogre::SceneManager &scnMgr, Ogre::String &name, const Ogre::String materialName);

	Ogre::Entity* GetEntity();

private:
	Ogre::Entity* entity;
};

