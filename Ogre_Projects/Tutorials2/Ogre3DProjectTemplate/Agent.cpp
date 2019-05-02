#include "Agent.h"

#include "AStar_Node.h"


#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreMath.h>



Agent::Agent()
{
	mCurrentNode = NULL;
	mEntity = NULL;
	g_scnMgr = nullptr;
	mSceneNode = NULL;
}


Agent::~Agent()
{
	if (mCurrentNode)
		delete mCurrentNode;
	if (mEntity)
		delete mEntity;
	if (mSceneNode)
		delete mSceneNode;
	if (g_scnMgr)
		delete g_scnMgr;
}


Agent::Agent(Ogre::SceneManager *& scnMgr)
{
	mCurrentNode = NULL;

	Setup(scnMgr);
}


Agent::Agent(AStar_Node *& currentNode, Ogre::SceneManager *& scnMgr)
{
	mCurrentNode = currentNode;
	
	Setup(scnMgr);
}


void Agent::Setup(Ogre::SceneManager *& scnMgr)
{
	g_scnMgr = scnMgr;
	mSceneNode = g_scnMgr->getRootSceneNode()->createChildSceneNode();
	mEntity = g_scnMgr->createEntity("ninja.mesh");
	mEntity->setMaterialName("Hurt");
	mSceneNode->attachObject(mEntity);

	mSceneNode->translate(Ogre::Vector3(-100, 0, -100));
	mSceneNode->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(180)), Ogre::Vector3::UNIT_Y));
	mEntity->setVisible(false);
}