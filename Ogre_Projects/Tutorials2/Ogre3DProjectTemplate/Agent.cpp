#include "Agent.h"

#include "AStar_Node.h"
#include "AStar.h"
#include "TileManager.h"


#include <OgreSceneManager.h>



Agent::Agent()
{
	mCurrentNode = NULL;
	mEntity = NULL;
	g_scnMgr = nullptr;
	mSceneNode = NULL;
	hidden = true;
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


void Agent::SetNode(AStar_Node * node)
{
	mCurrentNode = node;

	Ogre::Vector3* tempVec = new Ogre::Vector3(node->getPosition()->x, 0, node->getPosition()->y);

	mSceneNode->translate(*tempVec - mSceneNode->_getDerivedPosition());
	mSceneNode->translate(Ogre::Vector3(0, 60, 0));
	mEntity->setVisible(true);

	hidden = false;
}


AStar_Node * Agent::GetNode()
{
	return mCurrentNode;
}


void Agent::PathFind(TileManager * tileMgr)
{
	if (tileMgr->TilesReadyForTraversal() && !hidden)
	{
		tileMgr->SetupEdges();
		AList<AStar_Node*>* path = AStar::AStarSearch(mCurrentNode, tileMgr->GetGoalNode());
		Traverse(path, tileMgr);
		tileMgr->TearDownEdges();
		path->clear();
	}
}


void Agent::Reset()
{
	HideModel();
}


void Agent::Setup(Ogre::SceneManager *& scnMgr)
{
	g_scnMgr = scnMgr;
	mSceneNode = g_scnMgr->getRootSceneNode()->createChildSceneNode();
	mEntity = g_scnMgr->createEntity("Sinbad.mesh");
	mSceneNode->attachObject(mEntity);

	HideModel();

	mSceneNode->setScale(Ogre::Vector3(10, 10, 10));
}

void Agent::Traverse(AList<AStar_Node*>*& path, TileManager * tileMgr)
{
	for (std::reverse_iterator<AList<AStar_Node*>::iterator> iter = path->rbegin();
		iter != path->rend();
		iter++)
	{
		AStar_Node* node = *iter;
		SetNode(node);
		tileMgr->TraverseNode(node);
	}
}
