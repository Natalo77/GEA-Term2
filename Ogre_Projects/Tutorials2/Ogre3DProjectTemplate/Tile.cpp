#include "Tile.h"
#include "AStar_Node.h"

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSubEntity.h>





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
	//this->node->showBoundingBox(true);

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

	UpdateModel();

	return currentState;
}


void Tile::SetGoal()
{
	currentState = Tile::TILE_GOAL;

	UpdateModel();
}


Tile::State Tile::GetState()
{
	return currentState;
}


void Tile::ChangeMesh(Ogre::String &meshName, std::vector<Ogre::String> &materialNames)
{
	this->node->detachAllObjects();
	this->entity = this->scnMgr->createEntity(meshName);

	int i = 0;
	for (std::vector<Ogre::String>::iterator iter = materialNames.begin();
		iter != materialNames.end();
		iter++)
	{
		Ogre::String tempMatName = *iter;
		this->entity->getSubEntity(i)->setMaterialName(tempMatName);
		i++;
	}

	this->entity->setCastShadows(true);
	this->node->attachObject(this->entity);

}



