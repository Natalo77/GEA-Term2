#pragma once

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
	Tile();
	~Tile();
	Tile(
		Ogre::SceneManager &scnMgr, 
		Ogre::String &name, 
		const Ogre::String materialName,
		const Ogre::Vector3 &position,
		const Ogre::Quaternion &rotation);

	Ogre::Entity* GetEntity();

private:
	Ogre::Entity* entity;

	Ogre::SceneNode* node;
};

