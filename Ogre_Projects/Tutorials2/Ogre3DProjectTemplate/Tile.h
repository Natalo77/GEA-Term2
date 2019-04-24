#pragma once

namespace Ogre {
	class Entity;
	class SceneManager;
}

#include <OgreString.h>

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

