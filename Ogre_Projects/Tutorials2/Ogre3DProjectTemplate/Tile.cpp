#include "Tile.h"
#include "AStar_Node.h"

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>





Tile::Tile()
{
	entity = NULL;
	node = NULL;
	currentState = TILE_NA;
	scnMgr = nullptr;
	m_AStarNode = NULL;
}


Tile::~Tile()
{
	if(entity)
		delete entity;
	if(node)
		delete node;
	if (scnMgr)
		delete scnMgr;
	if (m_AStarNode)
		delete m_AStarNode;
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

	m_AStarNode = new AStar_Node(new Ogre::Vector2(position.x, position.z));
}


Ogre::Entity * Tile::GetEntity()
{
	return this->entity;
}


AStar_Node * Tile::GetNode()
{
	return m_AStarNode;
}


Tile::State Tile::CycleState()
{
	currentState++;

	Ogre::String newMeshString = getMeshName(currentState);
	Ogre::String newMaterialString = getMaterialName(currentState);

	ChangeMesh(newMeshString, newMaterialString);

	return currentState;
}


Tile::State Tile::GetState()
{
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



