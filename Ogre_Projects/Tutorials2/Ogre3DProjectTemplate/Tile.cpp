#include "Tile.h"

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>




Tile::Tile()
{
	entity = nullptr;
}


Tile::~Tile()
{
	delete entity;
}

Tile::Tile(
	Ogre::SceneManager & scnMgr, 
	Ogre::String & name, 
	const Ogre::String materialName,
	const Ogre::Vector3 &position,
	const Ogre::Quaternion &rotation)
{
	this->entity = scnMgr.createEntity(name);
	this->entity->setMaterialName(materialName);
	this->node = scnMgr.getRootSceneNode()->createChildSceneNode(position, rotation);
	this->node->attachObject(this->entity);
	this->node->showBoundingBox(true);
}

Ogre::Entity * Tile::GetEntity()
{
	return this->entity;
}

