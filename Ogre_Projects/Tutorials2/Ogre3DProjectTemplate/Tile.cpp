#include "Tile.h"

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>




Tile::Tile()
{
	entity = NULL;
	node = NULL;
	currentState = TILE_NA;
}


Tile::~Tile()
{
	delete entity;
	delete node;
}

Tile::Tile(
	Ogre::SceneManager & scnMgr, 
	Ogre::String & name, 
	const Ogre::String materialName,
	const Ogre::Vector3 &position,
	const Ogre::Quaternion &rotation)
{
	this->scnMgr = &scnMgr;
	this->currentState = TILE_GRASS;
	this->entity = this->scnMgr->createEntity(name);
	this->entity->setMaterialName(materialName);
	this->entity->setCastShadows(true);
	this->node = scnMgr.getRootSceneNode()->createChildSceneNode(position, rotation);
	this->node->attachObject(this->entity);
	this->node->showBoundingBox(true);
}

Ogre::Entity * Tile::GetEntity()
{
	return this->entity;
}

Tile::State Tile::CycleState()
{
	currentState++;

	Ogre::String newMeshString = getMeshName(currentState);
	Ogre::String newMaterialString = getMaterialName(currentState);

	ChangeMesh(newMeshString, newMaterialString);

	return currentState;
}

void Tile::ChangeMesh(Ogre::String meshName, Ogre::String materialName)
{
	this->node->detachAllObjects();
	this->entity = this->scnMgr->createEntity(meshName);
	this->entity->setMaterialName(materialName);
	this->entity->setCastShadows(true);
	this->node->attachObject(this->entity);

}



