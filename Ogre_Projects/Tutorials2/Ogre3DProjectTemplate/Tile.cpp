//=====================================================
//					Filename: Tile.cpp
//=====================================================


//=====================================================
//				Source Includes
//=====================================================
#include "Tile.h"
#include "AStar_Node.h"


//=====================================================
//					Library Includes
//=====================================================
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSubEntity.h>


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		Tile

Summary:	Default constructor of a Tile

Modifies:	[ALL MEMBERS]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
Tile::Tile()
{
	mEntity = NULL;
	mSceneNode = NULL;
	mCurrentState = TILE_NA;
	g_ScnMgr = nullptr;
	mAStarNode = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		~Tile

Summary:	Default deconstructor of a Tile

Modifies:	[ALL MEMBERS]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
Tile::~Tile()
{
	if(mEntity)
		delete mEntity;
	if(mSceneNode)
		delete mSceneNode;
	if (g_ScnMgr)
		delete g_ScnMgr;
	if (mAStarNode)
		delete mAStarNode;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		Tile

Summary:	preferred constructor of a Tile

Args:		SceneManager & g_ScnMgr
				reference to the scnMgr used to create this tile.
			String & name
				String to be used for the initial mesh of the tile.
			String materialName
				A string to be used for the initial material of the tile.
			Vector3 &position
				Vector3 to be used as the initial position of the tile.
			Quaternion & rotation
				Quaternion to be used as the initial rotation of the tile.

Modifies:	[ALL MEMBERS]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
Tile::Tile(
	Ogre::SceneManager & g_ScnMgr, 
	Ogre::String & name, 
	const Ogre::String materialName,
	const Ogre::Vector3 &position,
	const Ogre::Quaternion &rotation)
{
	// Set the reference to the scene manager.
	this->g_ScnMgr = &g_ScnMgr;

	// Set up the current state of the tile.
	this->mCurrentState = TILE_GRASS;

	// Set up the initial entity values.
	this->mEntity = this->g_ScnMgr->createEntity(name);
	this->mEntity->setMaterialName(materialName);
	this->mEntity->setCastShadows(true);

	// setup the initial sceneNode values.
	this->mSceneNode = g_ScnMgr.getRootSceneNode()->createChildSceneNode(position, rotation);
	this->mSceneNode->attachObject(this->mEntity);

	// Create the AStar node using the positional values.
	mAStarNode = new AStar_Node(new Ogre::Vector2(position.x, position.z));
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		GetEntity

Summary:	Return the Entity used by this tile.

Returns:	Entity*
				a pointer to the entity used by this tile.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
Ogre::Entity * Tile::GetEntity()
{
	return this->mEntity;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		GetNode

Summary:	Return the AStarNode used by this tile.

Returns:	AStar_Node*
				a pointer to the AStarNode used by this tile.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
AStar_Node * Tile::GetNode()
{
	return mAStarNode;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		CycleState

Summary:	Cycles the tile between valid states for cycling.

Returns:	State
				the state that was cycled to.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
Tile::State Tile::CycleState()
{
	// Incremement the state.
	mCurrentState++;

	// Update the model
	UpdateModel();

	// Return the new current state.
	return mCurrentState;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		reset

Summary:	Reset the tile back to its initial grass state.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void Tile::Reset()
{
	// Reset the AStarNode attached to this tile.
	mAStarNode->ResetNode();

	// Set the current state back to grass.
	mCurrentState = Tile::TILE_GRASS;

	// Update the model using the new state.
	UpdateModel();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		SetGoal

Summary:	Set this tile as a goal tile.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void Tile::SetGoal()
{
	// Set this tile's state as a goal tile.
	mCurrentState = Tile::TILE_GOAL;

	// Update the model using the new state.
	UpdateModel();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		GetState

Summary:	Return the currentState of this tile.

Returns:	State*
				the current state of this tile.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
Tile::State Tile::GetState()
{
	return mCurrentState;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		SetTraversed

Summary:	Set this tile as traversed upon
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void Tile::SetTraversed()
{
	// Set the current state as traversed.
	mCurrentState = Tile::TILE_TRAVERSED;

	// Update the model using the new state.
	UpdateModel();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		GetPosition

Summary:	Return the world space position of this tile.

Returns:	Vector3
				A vector3 for the world space position of this tile's
				sceneNode.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
Ogre::Vector3 Tile::GetPosition()
{
	return mSceneNode->_getDerivedPosition();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
Method:		ChangeMesh

Summary:	Change the Ogre rendering representation of this tile
			according to the passed in names of meshes and materials.

Args:		String & meshName
				the name of the mesh to be used for this model.
			vector<String> & materialNames
				a vector of material names to be used for this model.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void Tile::ChangeMesh(Ogre::String &meshName, std::vector<Ogre::String> &materialNames)
{
	// Detatch and deinitialize the existing entities.
	this->mSceneNode->detachAllObjects();
	this->mEntity->_deinitialise();

	// Create the new entity.
	this->mEntity = this->g_ScnMgr->createEntity(meshName);

	//iterate through the material names
	int i = 0;
	for (std::vector<Ogre::String>::iterator iter = materialNames.begin();
		iter != materialNames.end();
		iter++)
	{
		// Dereference the iterator.
		Ogre::String tempMatName = *iter;

		// For each material, assign it to the subEntity.
		this->mEntity->getSubEntity(i)->setMaterialName(tempMatName);
		i++;
	}

	// Set the entity to cast shadows.
	this->mEntity->setCastShadows(true);

	// Attach the object to the sceneNode.
	this->mSceneNode->attachObject(this->mEntity);

}



