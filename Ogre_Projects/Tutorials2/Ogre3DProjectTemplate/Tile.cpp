#include "Tile.h"

#include <OgreSceneManager.h>
#include <OgreEntity.h>




Tile::Tile()
{
	entity = nullptr;
}


Tile::~Tile()
{
	delete entity;
}

Tile::Tile(Ogre::SceneManager & scnMgr, Ogre::String & name, const Ogre::String materialName)
{
	this->entity = scnMgr.createEntity(name);
	this->entity->setMaterialName(materialName);
}

Ogre::Entity * Tile::GetEntity()
{
	return this->entity;
}

